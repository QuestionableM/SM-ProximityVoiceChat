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
	
	PlayerVoice(std::uint64_t steam_id, int player_id);
	~PlayerVoice();
	
	void push_voice(char* buffer, std::size_t buffer_size);
	
	void setVolume(float new_volume);
	float getVolume();

public:
	FMOD::Sound* m_pSound;
	FMOD::Channel* m_pChannel;

	std::uint64_t m_steamId;
	int m_playerId;
	float m_fVolume;

	std::mutex m_voiceMutex;
	std::vector<std::uint8_t> m_voiceData;
};

class PlayerVoiceManager
{
public:
	static PlayerVoice* GetVoice(int player_id);
	static bool PlayerHasVoice(int player_id);
	static void Update();

private:
	static void UpdatePlayerSound(Player* player, float master_volume);
	static void UpdatePlayerSounds();
	static void RemoveDeadVoices();

public:
	static std::unordered_map<int, std::shared_ptr<PlayerVoice>> sm_playerVoices;
};