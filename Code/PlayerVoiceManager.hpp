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
	
	void push_voice(char* buffer, std::size_t buffer_size)
	{
		std::lock_guard<std::mutex> v_lock_g(m_voiceMutex);

		std::uint8_t* v_data_start = reinterpret_cast<std::uint8_t*>(buffer);
		m_voiceData.insert(m_voiceData.end(), v_data_start, v_data_start + buffer_size);
	}
	
	~PlayerVoice()
	{
		if (m_pSound)
			m_pSound->release();
	}

public:
	FMOD::Sound* m_pSound = nullptr;
	FMOD::Channel* m_pChannel = nullptr;

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
	static void UpdatePlayerSound(Player* player);
	static void UpdatePlayerSounds();
	static void RemoveDeadVoices();

private:
	static std::unordered_map<int, std::shared_ptr<PlayerVoice>> sm_playerVoices;
};