#pragma once

#include "SmSdk/config.hpp"
#include "SmSdk/Util/Hashing.hpp"

#include <unordered_map>
#include <string>

SMSDK_BEGIN_NAMESPACE

class GameSettings
{
	SDK_PUB SMSDK_API static GameSettings* GetInstance();

	SDK_PUB SMSDK_API float getFloatSetting(const std::string_view& name, const float fDefaultValue = 1.0f) const;
	SDK_PUB SMSDK_API std::int32_t getIntSetting(const std::string_view& name, const std::int32_t iDefaultValue = 0) const;
	SDK_PUB SMSDK_API std::string_view getStringSetting(const std::string_view& name, const std::string_view& defaultValue = "") const;

	SDK_PUB SMSDK_API static float GetEffectsVolume();
	SDK_PUB SMSDK_API static float GetMasterVolume();

	SDK_PUB inline float getMasterVolume() const
	{
		return this->getFloatSetting("MasterVolume", 1.0f);
	}

	// Returns the actual value of EffectsVolume which is not affected by MasterVolume
	SDK_PUB inline float getEffectsVolumeRaw() const
	{
		return this->getFloatSetting("EffectVolume", 1.0f);
	}

	/* 0x0000 */ SDK_MEM_PUB std::unordered_map<std::string, int, Hashing::StringHash, std::equal_to<>> m_mapIntSettings;
	/* 0x0040 */ SDK_MEM_PUB std::unordered_map<std::string, float, Hashing::StringHash, std::equal_to<>> m_mapFloatSettings;
	/* 0x0080 */ SDK_MEM_PUB std::unordered_map<std::string, std::string, Hashing::StringHash, std::equal_to<>> m_mapStringSettings;
	/* 0x00C0 */ SDK_MEM_PUB std::int32_t m_appliedSettings;
	/* 0x00C4 */ SDK_MEM_PRI char pad_0xC4[0x4];
}; // Size: 0xC8

SMSDK_CHECK_MEMBER_OFFSET(GameSettings, m_mapIntSettings, 0x0);
SMSDK_CHECK_MEMBER_OFFSET(GameSettings, m_mapFloatSettings, 0x40);
SMSDK_CHECK_MEMBER_OFFSET(GameSettings, m_mapStringSettings, 0x80);
SMSDK_CHECK_MEMBER_OFFSET(GameSettings, m_appliedSettings, 0xC0);
SMSDK_CHECK_STRUCT_SIZE(GameSettings, 0xC8);

SMSDK_END_NAMESPACE