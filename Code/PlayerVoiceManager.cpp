#include "PlayerVoiceManager.hpp"

#include <SmSdk/Physics/CharacterPhysicsProxy.hpp>
#include <SmSdk/Character/CharacterManager.hpp>
#include <SmSdk/PlayerManager.hpp>
#include <SmSdk/AudioManager.hpp>
#include <SmSdk/GameSettings.hpp>
#include <SmSdk/MyPlayer.hpp>

#include <SmSdk/Gui/GuiInterface.hpp>
#include <SmSdk/Gui/GuiBase.hpp>

#include "VoiceSettingsStorage.hpp"
#include "VoiceManager.hpp"

#include "Utils/MathUtils.hpp"
#include "Utils/Console.hpp"

std::unordered_map<std::uint32_t, std::shared_ptr<PlayerVoice>> PlayerVoiceManager::sm_playerVoices = {};

FMOD_RESULT F_CALL PlayerVoice::pcm_callback(FMOD_SOUND* sound, void* data, unsigned int datalen)
{
	PlayerVoice* v_voice;
	if (FMOD_Sound_GetUserData(sound, reinterpret_cast<void**>(&v_voice)) == FMOD_OK)
	{
		std::lock_guard<std::mutex> v_lock(v_voice->m_voiceMutex);

		const std::size_t v_datalenSz = static_cast<std::size_t>(datalen);
		const std::size_t v_remData = std::min(v_voice->m_voiceData.size(), v_datalenSz);

		std::memcpy(data, v_voice->m_voiceData.data(), v_remData);
		if (v_datalenSz != v_remData)
			std::memset(reinterpret_cast<char*>(data) + v_remData, 0, v_datalenSz - v_remData);

		if (v_remData > 0)
			v_voice->m_voiceData.erase(v_voice->m_voiceData.begin(), v_voice->m_voiceData.begin() + v_remData);

		v_voice->m_isSpeaking = v_remData;
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
	, m_playerId(playerId)
	, m_fVolume(VoiceSettingsStorage::GetPlayerVolume(m_steamId))
	, m_fDistance(0.0f)
	, m_isSpeaking(false)
	, m_voiceMutex()
	, m_voiceData()
{}

PlayerVoice::~PlayerVoice()
{
	this->resetSound();
}

bool PlayerVoice::recreateStream(FMOD::System* pFmodSystem)
{
	this->resetSound();

	FMOD_CREATESOUNDEXINFO v_info;
	std::memset(&v_info, 0, sizeof(v_info));
	v_info.cbsize = sizeof(v_info);
	v_info.numchannels = 1;
	v_info.defaultfrequency = PVC_PLAYER_VOICE_FREQUENCY;
	v_info.decodebuffersize = 1024;
	v_info.length = v_info.defaultfrequency * v_info.numchannels * sizeof(std::uint16_t) * 5;
	v_info.format = FMOD_SOUND_FORMAT_PCM16;
	v_info.pcmreadcallback = PlayerVoice::pcm_callback;
	v_info.userdata = this;

	if (pFmodSystem->createStream(nullptr, FMOD_OPENUSER | FMOD_LOOP_NORMAL, &v_info, &m_pSound) != FMOD_OK)
	{
		DebugOutL("Couldn't create the sound for player: ", m_playerId);
		return false;
	}

	return true;
}

bool PlayerVoice::recreateFmodChannel(FMOD::System* pFmodSystem)
{
	if (pFmodSystem->playSound(m_pSound, nullptr, false, &m_pChannel) != FMOD_OK)
	{
		DebugOutL("Couldn't play the sound for player: ", m_playerId);
		return false;
	}

	m_pChannel->setMode(FMOD_3D | FMOD_3D_LINEARSQUAREROLLOFF);
	m_pChannel->set3DConeSettings(75.0f, 360.0f, 0.1f);
	m_pChannel->set3DMinMaxDistance(0.0f, 90.0f);
	m_pChannel->setReverbProperties(0, 0.0f);
	m_pChannel->setReverbProperties(1, 0.0f);
	m_pChannel->setReverbProperties(2, 0.0f);
	m_pChannel->setReverbProperties(3, 0.0f);

	return true;
}

void PlayerVoice::pushVoice(
	const void* buffer,
	const std::size_t bufferSz)
{
	if (!isChannelPlaying())
	{
		DebugOutL("Recreating the channel for player ", m_playerId);

		auto v_pAudioMgr = SM::AudioManager::GetInstance();
		if (!v_pAudioMgr) return;

		auto v_pFmodSystem = v_pAudioMgr->getFmodSystem();
		if (!v_pFmodSystem) return;

		if (!recreateFmodChannel(v_pFmodSystem))
			return;
	}

	std::lock_guard<std::mutex> v_lock(m_voiceMutex);

	const std::uint8_t* v_dataStart = reinterpret_cast<const std::uint8_t*>(buffer);
	m_voiceData.insert(m_voiceData.end(), v_dataStart, v_dataStart + bufferSz);
}

void PlayerVoice::setVolume(float new_volume)
{
	m_fVolume = new_volume;
	VoiceSettingsStorage::StorePlayerVolume(m_steamId, m_fVolume);
}

float PlayerVoice::getVolume() const
{
	if (m_fVolume <= 1.0f)
		return m_fVolume;

	return MathUtil::lerp(1.0f, 5.0f, m_fVolume - 1.0f);
}

float PlayerVoice::getFrequency() const
{
	float v_frequency = 0.0f;
	m_pChannel->getFrequency(&v_frequency);

	return v_frequency;
}

float PlayerVoice::getLoudness()
{
	std::lock_guard v_lock(m_voiceMutex);

	const std::size_t v_bytesAvailable = std::min<std::size_t>(m_voiceData.size(), 2048) / 2;
	if (v_bytesAvailable == 0) return 0.0f;

	float v_sum = 0.0f;
	for (std::size_t a = 0; a < v_bytesAvailable; a++)
	{
		const float v_curValue = static_cast<float>(reinterpret_cast<const std::int16_t*>(m_voiceData.data())[a]) / 32768.0f;
		v_sum += (v_curValue * v_curValue);
	}

	return std::sqrt(v_sum / float(v_bytesAvailable));
}

void PlayerVoice::resetSound()
{
	if (m_pSound)
	{
		m_pSound->release();
		m_pSound = nullptr;
	}
}

bool PlayerVoice::isChannelPlaying()
{
	if (!m_pChannel)
		return false;

	bool v_isPlaying;
	if (m_pChannel->isPlaying(&v_isPlaying) != FMOD_OK)
		return false;

	return v_isPlaying;
}

bool PlayerVoice::isSpeaking()
{
	return isChannelPlaying() && m_isSpeaking;
}

////////////////////PLAYER VOICE MANAGER/////////////////////

PlayerVoice* PlayerVoiceManager::GetVoice(const std::uint32_t playerId)
{
	auto v_iter = sm_playerVoices.find(playerId);
	if (v_iter != sm_playerVoices.end())
		return v_iter->second.get();

	return nullptr;
}

bool PlayerVoiceManager::IsVoicePlaying(const std::uint32_t playerId)
{
	PlayerVoice* v_pCurVoice = PlayerVoiceManager::GetVoice(playerId);
	if (!v_pCurVoice) return false;

	return v_pCurVoice->isSpeaking();
}

bool PlayerVoiceManager::PlayerHasVoice(const std::uint32_t playerId)
{
	return sm_playerVoices.contains(playerId);
}

void PlayerVoiceManager::Update(const float deltaTime)
{
	PlayerVoiceManager::UpdatePlayerSounds(deltaTime);
	PlayerVoiceManager::RemoveDeadVoices();
}

void PlayerVoiceManager::UpdatePlayerSound(SM::Player* player, const float deltaTime, const float masterVolume)
{
	// Players without the characters should not be processed
	if (!player->characterExists() || SM::MyPlayer::IsPlayerLocal(player))
		return;

	SM::AudioManager* v_pAudioMgr = SM::AudioManager::GetInstance();
	if (!v_pAudioMgr)
		return;

	const std::uint32_t v_playerId = player->getId();

	if (!PlayerVoiceManager::PlayerHasVoice(v_playerId))
	{
		AttachDebugConsole();

		auto v_pNewVoice = std::make_shared<PlayerVoice>(player->getSteamId(), v_playerId);
		FMOD::System* v_pFmodSystem = v_pAudioMgr->getFmodSystem();

		if (!v_pNewVoice->recreateStream(v_pFmodSystem))
			return;

		if (!v_pNewVoice->recreateFmodChannel(v_pFmodSystem))
			return;

		sm_playerVoices.emplace(v_playerId, std::move(v_pNewVoice));
		DebugOutL("Player voice created for player ", v_playerId);
		return;
	}

	PlayerVoice* v_pVoice = PlayerVoiceManager::GetVoice(v_playerId);
	if (!v_pVoice) return;

	auto v_pChar = player->getCharacter();
	if (!v_pChar) return;

	const float v_actualYaw = v_pChar->getYaw() + DirectX::XM_PIDIV2;
	FMOD_VECTOR v_data{ std::cos(v_actualYaw), 0.0f, std::sin(v_actualYaw) };
	v_pVoice->m_pChannel->set3DConeOrientation(&v_data);

	const float v_loudness = v_pVoice->getLoudness() * 400.0f;
	if (v_pVoice->m_fDistance < v_loudness)
		v_pVoice->m_fDistance = v_loudness;

	v_pVoice->m_fDistance *= std::expf(-1.0f * deltaTime);
	v_pVoice->m_pChannel->set3DMinMaxDistance(2.0f, std::max(2.0f, v_pVoice->m_fDistance));

	// Doppler effect calculation
	auto v_pSelfChar = SM::MyPlayer::GetCharacter();
	if (v_pSelfChar)
	{
		DirectX::XMFLOAT3 v_voiceVelocity = v_pChar->getVelocity();
		DirectX::XMFLOAT3 v_selfVelocity = v_pSelfChar->getVelocity();

		DirectX::FXMVECTOR v_voiceVelocityVec = DirectX::XMLoadFloat3(&v_voiceVelocity);
		DirectX::FXMVECTOR v_selfVelocityVec = DirectX::XMLoadFloat3(&v_selfVelocity);
		const float v_relativeVelocity = DirectX::XMVectorGetX(DirectX::XMVector3Length(DirectX::XMVectorSubtract(v_selfVelocityVec, v_voiceVelocityVec)));
		const float v_dopplerLevel = std::clamp(v_relativeVelocity, 0.0f, 50.0f) / 50.0f;

		v_pVoice->m_pChannel->set3DDopplerLevel(v_dopplerLevel);
	}

	const float v_charVelocityMultiplier = 0.5f;
	const DirectX::XMFLOAT3 v_charPosition = v_pChar->getPosition();
	const DirectX::XMFLOAT3 v_charVelocity = v_pChar->getVelocity();

	const FMOD_VECTOR v_objPos{ v_charPosition.x, v_charPosition.z, v_charPosition.y };
	const FMOD_VECTOR v_objVel{ v_charVelocity.x * v_charVelocityMultiplier, v_charVelocity.z * v_charVelocityMultiplier, v_charVelocity.y * v_charVelocityMultiplier };
	v_pVoice->m_pChannel->set3DAttributes(&v_objPos, &v_objVel);
	v_pVoice->m_pChannel->setVolume(v_pVoice->getVolume() * masterVolume);
}

void PlayerVoiceManager::UpdatePlayerSounds(const float deltaTime)
{
	const float v_masterVolume = SM::GameSettings::GetMasterVolume();

	for (const auto& v_pCurPlayer : SM::PlayerManager::GetAllPlayers())
	{
		PlayerVoiceManager::UpdatePlayerSound(v_pCurPlayer.get(), deltaTime, v_masterVolume);
		PlayerVoiceManager::UpdatePlayerNameTag(v_pCurPlayer.get());
	}
}

void PlayerVoiceManager::UpdatePlayerNameTag(SM::Player* player)
{
	auto v_pCurChar = player->getCharacter();
	if (!v_pCurChar) return;

	auto v_pNameTagGui = v_pCurChar->getNameTagGui();
	if (!v_pNameTagGui) return;

	auto v_pGuiBase = v_pNameTagGui->getGuiBase();
	if (!v_pGuiBase) return;

	auto v_pMainPanel = v_pGuiBase->getMainPanel();
	if (!v_pMainPanel) return;

	if (v_pMainPanel->isVisible()
		&& PlayerVoiceManager::IsVoicePlaying(player->getId()))
	{
		MyGUI::ImageBox* v_pSpeakerIcon = VoiceManager::GetSpeakerImageBox(v_pMainPanel);

		// Adjust to fit the text
		MyGUI::EditBox* v_pWidget = v_pMainPanel->findWidget("Text")->castType<MyGUI::EditBox>(false);
		if (v_pWidget && v_pWidget->getTextLength() > 0)
		{
			const MyGUI::IntSize v_textSize = v_pWidget->getTextSize();

			const int v_textSizeHeightAdjusted = static_cast<int>(float(v_textSize.height) * 1.25f);
			const MyGUI::IntSize v_mainPanelSz(v_textSize.width + v_textSizeHeightAdjusted, v_textSizeHeightAdjusted);
			v_pMainPanel->setSize(v_mainPanelSz);

			v_pWidget->setTextAlign(MyGUI::Align::VCenter | MyGUI::Align::Right);
			v_pWidget->setSize(v_pWidget->getWidth(), v_pMainPanel->getHeight());

			v_pSpeakerIcon->setPosition(v_pMainPanel->getWidth() - v_pSpeakerIcon->getWidth(), 0);
			v_pSpeakerIcon->setSize(v_mainPanelSz.height, v_mainPanelSz.height);
			v_pSpeakerIcon->setVisible(true);

			return;
		}
	}

	MyGUI::ImageBox* v_pSpeakerIcon = VoiceManager::GetSpeakerImageBox(v_pMainPanel, false);
	if (v_pSpeakerIcon)
		v_pSpeakerIcon->setVisible(false);
}

void PlayerVoiceManager::RemoveDeadVoices()
{
	for (auto v_iter = sm_playerVoices.begin(); v_iter != sm_playerVoices.end();)
	{
		auto v_pCurPlayer = SM::PlayerManager::GetPlayer(v_iter->first);
		if (v_pCurPlayer != nullptr && v_pCurPlayer->characterExists())
		{
			v_iter++;
			continue;
		}

		DebugOutL("Removed player voice for player id: ", v_iter->first);
		v_iter = sm_playerVoices.erase(v_iter);
	}
}