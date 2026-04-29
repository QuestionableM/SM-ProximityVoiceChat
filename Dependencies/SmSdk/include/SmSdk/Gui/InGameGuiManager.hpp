#pragma once

#include "SmSdk/config.hpp"

#include "SmSdk/Gui/InGameGuiManagerInterface.hpp"
#include "SmSdk/Gui/InventoryGui.hpp"
#include "SmSdk/Gui/HudGui2.hpp"

SMSDK_BEGIN_NAMESPACE

class InGameGuiManager : public InGameGuiManagerInterface
{
	REMOVE_COPY_CONSTRUCTORS(InGameGuiManager);
	SDK_PUB virtual ~InGameGuiManager() = default;

	SDK_PUB SMSDK_API static InGameGuiManager* GetInstance();

	SDK_PUB SMSDK_API void displayAlertText(const std::string_view& text, const float duration = 4.0f);
	SDK_PUB SMSDK_API void setInteractionText(const std::vector<std::string>& vec);

	SDK_PUB SMSDK_API static void DisplayAlertText(const std::string_view& text, const float duration = 4.0f);
	SDK_PUB SMSDK_API static void SetInteractionText(const std::vector<std::string>& vec);

	/* 0x0008 */ SDK_PRI char pad_0x8[0x18];
	/* 0x0020 */ SDK_PUB std::shared_ptr<HudGui2> m_pHudGui;
	/* 0x0030 */ SDK_PUB std::shared_ptr<InventoryGui> m_pInventory;
	/* 0x0040 */ SDK_PRI char pad_0x40[0x18];
	/* 0x0058 */ SDK_PRI char pad_0x58[0x198];
}; // Size: 0x1F0

static_assert(sizeof(InGameGuiManager) == 0x1F0, "InGameGuiManager: Incorrect Size");

SMSDK_END_NAMESPACE