#pragma once

#include <unordered_map>

#define VSS_CONFIG_PATH "./smpvc_config.txt"

class VoiceSettingsStorage
{
public:
	using VoiceMap = std::unordered_map<std::uint64_t, float>;

	static void LoadConfig();
	static void SaveConfig();

	static void Update(float dt);
	static float GetPlayerVolume(std::uint64_t steam_id);
	static void StorePlayerVolume(std::uint64_t steam_id, float new_volume);

private:
	static VoiceMap sm_steamIdToVolume;
	static float sm_fConfigSaveTimer;
	static bool sm_bConfigLoaded;

	VoiceSettingsStorage() = default;
	VoiceSettingsStorage(const VoiceSettingsStorage&) = delete;
	VoiceSettingsStorage(VoiceSettingsStorage&&) = delete;
	~VoiceSettingsStorage() = default;
};