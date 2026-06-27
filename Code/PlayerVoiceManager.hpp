#pragma once

#include "SmSdk/Player.hpp"

#include <fmod/fmod_studio.hpp>
#include <fmod/fmod.hpp>

#include <unordered_map>
#include <memory>
#include <vector>
#include <mutex>

class PlayerVoice
{
public:
	static FMOD_RESULT F_CALL pcm_callback(FMOD_SOUND* sound, void* data, unsigned int datalen);
	
	PlayerVoice(const std::uint64_t steamId, const std::uint32_t playerId);
	~PlayerVoice();
	
	bool recreateStream(FMOD::System* pFmodSystem);
	bool recreateFmodChannel(FMOD::System* pFmodSystem);
	void pushVoice(const void* buffer, const std::size_t bufferSz);
	
	void setVolume(float new_volume);
	float getVolume();

	void resetSound();
	bool isChannelPlaying();
	bool isSpeaking();

public:
	FMOD::Sound* m_pSound;
	FMOD::Channel* m_pChannel;

	std::uint64_t m_steamId;
	std::uint32_t m_playerId;
	float m_fVolume;
	std::atomic_bool m_isSpeaking;

	std::mutex m_voiceMutex;
	std::vector<std::uint8_t> m_voiceData;
};

class PlayerVoiceManager
{
public:
	static PlayerVoice* GetVoice(const std::uint32_t playerId);
	static bool IsVoicePlaying(const std::uint32_t playerId);

	static bool PlayerHasVoice(const std::uint32_t playerId);
	static void Update(const float deltaTime);

private:
	static void UpdatePlayerSound(SM::Player* player, const float deltaTime, const float masterVolume);
	static void UpdatePlayerSounds(const float deltaTime);
	static void UpdatePlayerNameTag(SM::Player* player);
	static void RemoveDeadVoices();

public:
	static std::unordered_map<std::uint32_t, std::shared_ptr<PlayerVoice>> sm_playerVoices;
};