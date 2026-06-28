#include "VoiceSettingsStorage.hpp"

#include "Utils/Console.hpp"

#include <fstream>

VoiceSettingsStorage::VoiceMap VoiceSettingsStorage::sm_steamIdToVolume = {};
float VoiceSettingsStorage::sm_fConfigSaveTimer = 0.0f;
bool VoiceSettingsStorage::sm_bConfigLoaded = false;


void VoiceSettingsStorage::LoadConfig()
{
	//Makes it so the config can be loaded only once
	if (sm_bConfigLoaded) return;
	sm_bConfigLoaded = true;

	AttachDebugConsole();
	DebugOutL(__FUNCTION__);

	std::ifstream v_conf_loader(VSS_CONFIG_PATH);
	if (!v_conf_loader.is_open()) return;

	float v_volume;
	std::uint64_t v_steam_id;

	while (true)
	{
		if (!(v_conf_loader >> v_steam_id)) break;
		if (!(v_conf_loader >> v_volume)) break;

		const float v_storedVolume = std::max(std::min(v_volume, 4.0f), 0.0f);
		DebugOutL(__FUNCTION__ " -> SteamId: ", v_steam_id, ", Volume: ", v_storedVolume);
		sm_steamIdToVolume.emplace(v_steam_id, v_storedVolume);
	}
}

void VoiceSettingsStorage::SaveConfig()
{
	AttachDebugConsole();
	DebugOutL(__FUNCTION__);

	std::ofstream v_conf_writer(VSS_CONFIG_PATH);
	if (!v_conf_writer.is_open())
	{
		DebugErrorL("Couldn't save the config to: ", VSS_CONFIG_PATH);
		return;
	}

	for (const auto& v_cur_item : sm_steamIdToVolume)
	{
		//Skip the default volume settings to decrease file size
		if (v_cur_item.second == 1.0f) continue;

		v_conf_writer << v_cur_item.first << " " << v_cur_item.second << std::endl;
	}
}

void VoiceSettingsStorage::Update(const float dt)
{
	VoiceSettingsStorage::LoadConfig();

	if (sm_fConfigSaveTimer > 0.0f)
	{
		sm_fConfigSaveTimer -= dt;

		if (sm_fConfigSaveTimer <= 0.0f)
			VoiceSettingsStorage::SaveConfig();
	}
}

float VoiceSettingsStorage::GetPlayerVolume(const std::uint64_t steamId)
{
	auto v_iter = sm_steamIdToVolume.find(steamId);
	if (v_iter != sm_steamIdToVolume.end())
		return v_iter->second;

	return 1.0f;
}

void VoiceSettingsStorage::StorePlayerVolume(const std::uint64_t steamId, const float fNewVolume)
{
	auto v_iter = sm_steamIdToVolume.find(steamId);
	if (v_iter != sm_steamIdToVolume.end())
		v_iter->second = fNewVolume;
	else
		sm_steamIdToVolume.emplace(steamId, fNewVolume);

	sm_fConfigSaveTimer = 5.0f;
}