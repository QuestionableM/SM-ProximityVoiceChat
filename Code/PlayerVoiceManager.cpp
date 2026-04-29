#include "PlayerVoiceManager.hpp"

#include <SmSdk/Physics/CharacterPhysicsProxy.hpp>
#include <SmSdk/CharacterManager.hpp>
#include <SmSdk/PlayerManager.hpp>
#include <SmSdk/AudioManager.hpp>
#include <SmSdk/GameSettings.hpp>
#include <SmSdk/MyPlayer.hpp>

#include "VoiceSettingsStorage.hpp"
#include "Utils/MathUtils.hpp"
#include "Utils/Console.hpp"

std::unordered_map<std::uint32_t, std::shared_ptr<PlayerVoice>> PlayerVoiceManager::sm_playerVoices = {};

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

PlayerVoice::PlayerVoice(
	const std::uint64_t steamId,
	const std::uint32_t playerId
)
	: m_pSound(nullptr)
	, m_pChannel(nullptr)
	, m_steamId(steamId)
	, m_fVolume(VoiceSettingsStorage::GetPlayerVolume(m_steamId))
	, m_voiceMutex()
	, m_voiceData()
{}

PlayerVoice::~PlayerVoice()
{
	if (m_pSound)
		m_pSound->release();
}

void PlayerVoice::push_voice(char* buffer, std::size_t buffer_size)
{
	std::lock_guard<std::mutex> v_lock(m_voiceMutex);

	std::uint8_t* v_dataStart = reinterpret_cast<std::uint8_t*>(buffer);
	m_voiceData.insert(m_voiceData.end(), v_dataStart, v_dataStart + buffer_size);
}

void PlayerVoice::setVolume(float new_volume)
{
	m_fVolume = new_volume;
	VoiceSettingsStorage::StorePlayerVolume(m_steamId, m_fVolume);
}

float PlayerVoice::getVolume()
{
	if (m_fVolume <= 1.0f)
		return m_fVolume;

	return MathUtil::lerp(1.0f, 5.0f, m_fVolume - 1.0f);
}

////////////////////PLAYER VOICE MANAGER/////////////////////

PlayerVoice* PlayerVoiceManager::GetVoice(const std::uint32_t playerId)
{
	auto v_iter = sm_playerVoices.find(playerId);
	if (v_iter != sm_playerVoices.end())
		return v_iter->second.get();

	return nullptr;
}

bool PlayerVoiceManager::PlayerHasVoice(const std::uint32_t playerId)
{
	return sm_playerVoices.contains(playerId);
}

void PlayerVoiceManager::Update()
{
	PlayerVoiceManager::UpdatePlayerSounds();
	PlayerVoiceManager::RemoveDeadVoices();
}

static bool IsPlayerLocal(SM::Player* pPlayer)
{
	SM::MyPlayer* v_pMyPlayer = SM::MyPlayer::GetInstance();
	if (!v_pMyPlayer)
		return false;

	SM::Player* v_pPlayer = v_pMyPlayer->getPlayer();
	if (!v_pPlayer)
		return false;

	return v_pPlayer->getSteamId() == pPlayer->getSteamId();
}

void PlayerVoiceManager::UpdatePlayerSound(SM::Player* player, const float masterVolume)
{
	//Players without the characters should not be processed
	if (!player->characterExists() || IsPlayerLocal(player))
		return;

	SM::AudioManager* v_pAudioMgr = SM::AudioManager::GetInstance();
	if (!v_pAudioMgr)
		return;

	const std::uint32_t v_playerId = player->getId();

	if (!PlayerVoiceManager::PlayerHasVoice(v_playerId))
	{
		AttachDebugConsole();

		auto v_pNewVoice = std::make_shared<PlayerVoice>(player->getSteamId(), v_playerId);

		FMOD_CREATESOUNDEXINFO v_info;
		std::memset(&v_info, 0, sizeof(v_info));
		v_info.cbsize = sizeof(v_info);
		v_info.numchannels = 1;
		v_info.defaultfrequency = 11000;
		v_info.decodebuffersize = 11000;
		v_info.length = v_info.defaultfrequency * v_info.numchannels * sizeof(float) * 5;
		v_info.format = FMOD_SOUND_FORMAT_PCM16;
		v_info.pcmreadcallback = PlayerVoice::pcm_callback;
		v_info.userdata = v_pNewVoice.get();

		FMOD::System* v_pFmodSystem = v_pAudioMgr->getFmodSystem();

		FMOD_RESULT v_hr = v_pFmodSystem->createStream(
			nullptr, FMOD_OPENUSER | FMOD_LOOP_NORMAL, &v_info, &v_pNewVoice->m_pSound);
		if (v_hr != FMOD_OK)
		{
			DebugOutL("Couldn't create the sound for player ", v_playerId);
			return;
		}

		v_hr = v_pFmodSystem->playSound(
			v_pNewVoice->m_pSound, nullptr, false, &v_pNewVoice->m_pChannel);
		if (v_hr != FMOD_OK)
		{
			DebugOutL("Couldn't play the sound for player ", v_playerId);
			return;
		}

		v_pNewVoice->m_pChannel->setMode(FMOD_3D | FMOD_3D_LINEARSQUAREROLLOFF);
		v_pNewVoice->m_pChannel->set3DConeSettings(75.0f, 360.0f, 0.1f);
		v_pNewVoice->m_pChannel->set3DMinMaxDistance(0.0f, 90.0f);
		v_pNewVoice->m_pChannel->setReverbProperties(0, 0.0f);
		v_pNewVoice->m_pChannel->setReverbProperties(1, 0.0f);
		v_pNewVoice->m_pChannel->setReverbProperties(2, 0.0f);
		v_pNewVoice->m_pChannel->setReverbProperties(3, 0.0f);

		sm_playerVoices.emplace(v_playerId, std::move(v_pNewVoice));
		DebugOutL("Player voice created for player ", v_playerId);
		return;
	}

	PlayerVoice* v_pVoice = PlayerVoiceManager::GetVoice(v_playerId);
	if (!v_pVoice) return;

	SM::Character* v_pChar = player->getCharacter();
	if (!v_pChar) return;

	const float v_actualYaw = v_pChar->getYaw() + DirectX::XM_PIDIV2;
	FMOD_VECTOR v_data{ std::cos(v_actualYaw), std::sin(v_actualYaw), 0.0f };
	v_pVoice->m_pChannel->set3DConeOrientation(&v_data);

	const DirectX::XMFLOAT3 v_charPosition = v_pChar->getPosition();
	const DirectX::XMFLOAT3 v_charVelocity = v_pChar->getVelocity();

	const FMOD_VECTOR v_objPos{ v_charPosition.x, v_charPosition.z, v_charPosition.y };
	const FMOD_VECTOR v_objVel{ v_charVelocity.x, v_charVelocity.z, v_charVelocity.y };
	v_pVoice->m_pChannel->set3DAttributes(&v_objPos, &v_objVel);

	v_pVoice->m_pChannel->setVolume(v_pVoice->getVolume() * masterVolume);
}

void PlayerVoiceManager::UpdatePlayerSounds()
{
	SM::PlayerManager* v_pl_mgr = SM::PlayerManager::GetInstance();
	if (!v_pl_mgr) return;

	const float v_master_volume = SM::GameSettings::GetMasterVolume();

	for (const auto& v_cur_iter : v_pl_mgr->m_mapIdToPlayers)
	{
		if (!v_cur_iter.second) continue;

		PlayerVoiceManager::UpdatePlayerSound(v_cur_iter.second.get(), v_master_volume);
	}
}

void PlayerVoiceManager::RemoveDeadVoices()
{
	for (auto v_iter = sm_playerVoices.begin(); v_iter != sm_playerVoices.end();)
	{
		SM::Player* v_cur_player = SM::PlayerManager::GetPlayer(v_iter->first);
		if (v_cur_player != nullptr && v_cur_player->characterExists())
		{
			v_iter++;
			continue;
		}

		DebugOutL("Removed player voice for player id: ", v_iter->first);
		v_iter = sm_playerVoices.erase(v_iter);
	}
}