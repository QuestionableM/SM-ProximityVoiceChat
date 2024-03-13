#include "PlayerVoiceManager.hpp"

#include "SmSdk/Physics/CharacterPhysicsProxy.hpp"
#include "SmSdk/CharacterManager.hpp"
#include "SmSdk/PlayerManager.hpp"
#include "SmSdk/AudioManager.hpp"

#include "Utils/Console.hpp"

std::unordered_map<int, std::shared_ptr<PlayerVoice>> PlayerVoiceManager::sm_playerVoices = {};

FMOD_RESULT F_CALL PlayerVoice::pcm_callback(FMOD_SOUND* sound, void* data, unsigned int datalen)
{
	PlayerVoice* v_voice = nullptr;
	FMOD_Sound_GetUserData(sound, reinterpret_cast<void**>(&v_voice));

	std::lock_guard<std::mutex> v_lock_g(v_voice->m_voiceMutex);

	const std::size_t v_datalen_sz = std::size_t(datalen);
	const std::size_t v_rem_data = std::min(v_voice->m_voiceData.size(), v_datalen_sz);

	std::memcpy(data, v_voice->m_voiceData.data(), v_rem_data);
	if (v_datalen_sz != v_rem_data)
		std::memset(reinterpret_cast<char*>(data) + v_rem_data, 0, v_datalen_sz - v_rem_data);

	if (v_rem_data > 0)
	{
		v_voice->m_voiceData.erase(
			v_voice->m_voiceData.begin(),
			v_voice->m_voiceData.begin() + v_rem_data);
	}
	
	return FMOD_OK;
}

PlayerVoice* PlayerVoiceManager::GetVoice(int player_id)
{
	auto v_iter = sm_playerVoices.find(player_id);
	if (v_iter != sm_playerVoices.end())
		return v_iter->second.get();

	return nullptr;
}

bool PlayerVoiceManager::PlayerHasVoice(int player_id)
{
	return sm_playerVoices.find(player_id) != sm_playerVoices.end();
}

void PlayerVoiceManager::Update()
{
	PlayerVoiceManager::UpdatePlayerSounds();
	PlayerVoiceManager::RemoveDeadVoices();
}

void PlayerVoiceManager::UpdatePlayerSound(Player* player)
{
	//Players without the characters should not be processed
	if (player->character_id == -1) return;

	AudioManager* v_aud_mgr = AudioManager::GetInstance();
	if (!v_aud_mgr) return;

	if (!PlayerVoiceManager::PlayerHasVoice(player->id))
	{
		AttachDebugConsole();

		auto v_new_voice = std::make_shared<PlayerVoice>();

		FMOD_CREATESOUNDEXINFO v_info;
		std::memset(&v_info, 0, sizeof(v_info));
		v_info.cbsize = sizeof(v_info);
		v_info.numchannels = 1;
		v_info.defaultfrequency = 11000;
		v_info.decodebuffersize = 11000;
		v_info.length = v_info.defaultfrequency * v_info.numchannels * sizeof(float) * 5;
		v_info.format = FMOD_SOUND_FORMAT_PCM16;
		v_info.pcmreadcallback = PlayerVoice::pcm_callback;
		v_info.userdata = v_new_voice.get();

		FMOD_RESULT v_hr = v_aud_mgr->fmod_system->createStream(
			nullptr, FMOD_OPENUSER | FMOD_LOOP_NORMAL, &v_info, &v_new_voice->m_pSound);

		if (v_hr != FMOD_OK)
		{
			DebugOutL("Couldn't create the sound for player ", player->id);
			return;
		}

		v_hr = v_aud_mgr->fmod_system->playSound(
			v_new_voice->m_pSound, nullptr, false, &v_new_voice->m_pChannel);

		if (v_hr != FMOD_OK)
		{
			DebugOutL("Couldn't play the sound for player ", player->id);
			return;
		}

		v_new_voice->m_pChannel->setMode(FMOD_3D);
		v_new_voice->m_pChannel->set3DConeSettings(30.0f, 360.0f, 0.01f);
		v_new_voice->m_pChannel->set3DMinMaxDistance(0.01f, 10000.0f);
		v_new_voice->m_pChannel->setVolume(200.0f);
		v_new_voice->m_pChannel->setReverbProperties(0, 0.0f);
		v_new_voice->m_pChannel->setReverbProperties(1, 0.0f);
		v_new_voice->m_pChannel->setReverbProperties(2, 0.0f);
		v_new_voice->m_pChannel->setReverbProperties(3, 0.0f);

		sm_playerVoices.emplace(player->id, std::move(v_new_voice));
		DebugOutL("Player voice created for player ", player->id);
		DebugOutL(__FUNCTION__, " -> ID: ", player->id, ", Character: ", player->character_id);
		return;
	}

	auto v_voice_iter = sm_playerVoices.find(player->id);
	if (v_voice_iter == sm_playerVoices.end()) return;

	PlayerVoice* v_pl_voice = v_voice_iter->second.get();
	if (!v_pl_voice) return;

	Character* v_char = CharacterManager::GetCharacter(player->character_id);
	if (!v_char) return;

	const float v_actual_yaw = v_char->yaw + DirectX::XM_PIDIV2;
	FMOD_VECTOR v_data{ std::cos(v_actual_yaw), std::sin(v_actual_yaw), 0.0f };
	v_pl_voice->m_pChannel->set3DConeOrientation(&v_data);

	const btVector3& v_bt_obj_pos = v_char->physics_proxy->m_pTickRaycastCollisionObject->getWorldTransform().getOrigin();
	const FMOD_VECTOR v_obj_pos{ v_bt_obj_pos.x(), v_bt_obj_pos.z(), v_bt_obj_pos.y() };
	const FMOD_VECTOR v_obj_vel{ v_char->velocity.x, v_char->velocity.z, v_char->velocity.y };
	v_pl_voice->m_pChannel->set3DAttributes(&v_obj_pos, &v_obj_vel);
}

void PlayerVoiceManager::UpdatePlayerSounds()
{
	PlayerManager* v_pl_mgr = PlayerManager::GetInstance();
	if (!v_pl_mgr) return;

	for (const auto& v_cur_iter : v_pl_mgr->id_to_player_map)
	{
		if (!v_cur_iter.second) continue;

		PlayerVoiceManager::UpdatePlayerSound(v_cur_iter.second.get());
	}
}

void PlayerVoiceManager::RemoveDeadVoices()
{
	for (auto v_iter = sm_playerVoices.begin(); v_iter != sm_playerVoices.end();)
	{
		Player* v_cur_player = PlayerManager::GetPlayer(v_iter->first);
		if (v_cur_player != nullptr && v_cur_player->character_id > -1)
		{
			v_iter++;
			continue;
		}

		DebugOutL("Removed player voice for player id: ", v_iter->first);
		v_iter = sm_playerVoices.erase(v_iter);
	}
}