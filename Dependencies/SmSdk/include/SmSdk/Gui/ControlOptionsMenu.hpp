#pragma once

#include "SmSdk/Gui/OptionsSubMenuBase.hpp"

#include "SmSdk/Util/Memory.hpp"
#include "SmSdk/offsets.hpp"

SMSDK_BEGIN_NAMESPACE

class ControlOptionsMenu : public OptionsSubMenuBase
{
	SDK_PUB SMSDK_API static ControlOptionsMenu* New();
	SDK_PRI SMSDK_API ControlOptionsMenu();

	SDK_PUB virtual ~ControlOptionsMenu() = default;
	SDK_PUB void restoreDefaults() override { /* implemented by the game */ }

	/* 0x0168 */ SDK_MEM_PRI char pad_0x168[0x20];
}; // Size: 0x188

SMSDK_CHECK_STRUCT_SIZE(ControlOptionsMenu, 0x188);

SMSDK_END_NAMESPACE