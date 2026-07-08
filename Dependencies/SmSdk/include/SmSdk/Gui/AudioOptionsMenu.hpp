#pragma once

#include "SmSdk/Gui/OptionsSubMenuBase.hpp"

#include "SmSdk/Util/Memory.hpp"
#include "SmSdk/offsets.hpp"

SMSDK_BEGIN_NAMESPACE

class AudioOptionsMenu : public OptionsSubMenuBase
{
	SDK_PUB SMSDK_API static AudioOptionsMenu* New();
	SDK_PRI SMSDK_API AudioOptionsMenu();

	SDK_PUB virtual ~AudioOptionsMenu() = default;
	SDK_PUB void restoreDefaults() override { /* implemented by the game */ }
}; // Size: 0x168

SMSDK_CHECK_STRUCT_SIZE(AudioOptionsMenu, 0x168);

SMSDK_END_NAMESPACE