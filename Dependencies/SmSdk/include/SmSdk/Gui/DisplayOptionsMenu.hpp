#pragma once

#include "SmSdk/Gui/OptionsSubMenuBase.hpp"

#include "SmSdk/Util/Memory.hpp"
#include "SmSdk/offsets.hpp"

SMSDK_BEGIN_NAMESPACE

class DisplayOptionsMenu : public OptionsSubMenuBase
{
	SDK_PUB SMSDK_API static DisplayOptionsMenu* New();
	SDK_PRI SMSDK_API DisplayOptionsMenu();

	SDK_PUB virtual ~DisplayOptionsMenu() = default;
	SDK_PUB void restoreDefaults() override { /* implemented by the game */ }

	/* 0x0168 */ SDK_PRI char pad_0x168[0xD0];
}; // Size: 0x238

static_assert(sizeof(DisplayOptionsMenu) == 0x238, "DisplayOptionsMenu: Incorrect Size");

SMSDK_END_NAMESPACE