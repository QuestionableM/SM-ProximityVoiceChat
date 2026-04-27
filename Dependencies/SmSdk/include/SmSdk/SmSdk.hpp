#pragma once

#include "SmSdk/config.hpp"
#include "SmSdk/win_include.hpp"

#define _SM_TIMESTAMP_070_771 1733399248
#define _SM_TIMESTAMP_071_772 1733491522
#define _SM_TIMESTAMP_072_775 1733754961
#define _SM_TIMESTAMP_073_776 1733837301
#define _SM_TIMESTAMP_074_778 1772468471

namespace SmSdk
{
	// Local function that just checks if SmSdk is present in the process
	static bool IsLoaded()
	{
		return GetModuleHandleA("SmSdk.dll") != nullptr;
	}

	// Checks the versions of the loaded module by its timestamp
	SMSDK_API bool CheckTimestamp(const std::uint32_t timeStamp);
}