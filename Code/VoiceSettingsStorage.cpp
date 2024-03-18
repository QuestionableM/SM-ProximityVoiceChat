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

		DebugOutL(__FUNCTION__ " -> SteamId: ", v_steam_id, ", Volume: ", std::max(std::min(v_volume, 2.0f), 0.0f));
		sm_steamIdToVolume.emplace(v_steam_id, std::max(std::min(v_volume, 2.0f), 0.0f));
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

void VoiceSettingsStorage::Update(float dt)
{
	VoiceSettingsStorage::LoadConfig();

	if (sm_fConfigSaveTimer > 0.0f)
	{
		sm_fConfigSaveTimer -= dt;

		if (sm_fConfigSaveTimer <= 0.0f)
			VoiceSettingsStorage::SaveConfig();
	}
}

float VoiceSettingsStorage::GetPlayerVolume(std::uint64_t steam_id)
{
	auto v_iter = sm_steamIdToVolume.find(steam_id);
	if (v_iter != sm_steamIdToVolume.end())
		return v_iter->second;

	return 1.0f;
}

void VoiceSettingsStorage::StorePlayerVolume(std::uint64_t steam_id, float new_volume)
{
	auto v_iter = sm_steamIdToVolume.find(steam_id);
	if (v_iter != sm_steamIdToVolume.end())
		v_iter->second = new_volume;
	else
		sm_steamIdToVolume.emplace(steam_id, new_volume);

	sm_fConfigSaveTimer = 5.0f;
}