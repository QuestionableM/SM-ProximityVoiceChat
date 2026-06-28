#pragma once

#include "SmSdk/Gui/InGameGuiManagerInterface.hpp"
#include "SmSdk/config.hpp"

#include <string>
#include <vector>
#include <memory>

SMSDK_BEGIN_NAMESPACE

class InGameGuiManager : public InGameGuiManagerInterface
{
	REMOVE_COPY_CONSTRUCTORS(InGameGuiManager);
	SDK_PUB virtual ~InGameGuiManager() = default;

	SDK_PUB SMSDK_API static InGameGuiManager* GetInstance();

	SDK_PUB SMSDK_API void chatMessage(const std::string_view& text, const std::string_view& author = "");
	SDK_PUB SMSDK_API void displayAlertText(const std::string_view& text, const float duration = 4.0f);
	SDK_PUB SMSDK_API void setInteractionText(const std::vector<std::string>& vec);

	SDK_PUB SMSDK_API static void ChatMessage(const std::string_view& text, const std::string_view& author = "");
	SDK_PUB SMSDK_API static void DisplayAlertText(const std::string_view& text, const float duration = 4.0f);
	SDK_PUB SMSDK_API static void SetInteractionText(const std::vector<std::string>& vec);

	SDK_PUB SMSDK_API std::shared_ptr<class HudGui2> getHudGui();
	SDK_PUB SMSDK_API std::shared_ptr<class InventoryGui> getInventoryGui();
	SDK_PUB SMSDK_API std::shared_ptr<class ChatGui> getChatGui();

	SDK_PUB SMSDK_API static std::shared_ptr<class HudGui2> GetHudGui();
	SDK_PUB SMSDK_API static std::shared_ptr<class InventoryGui> GetInventoryGui();
	SDK_PUB SMSDK_API static std::shared_ptr<class ChatGui> GetChatGui();

	SDK_PUB SMSDK_API bool isGuiHidden() const;
	SDK_PUB SMSDK_API static bool IsGuiHidden();

	/* 0x0008 */ SDK_PUB bool m_bDefaultGuisInitialized;
	/* 0x0009 */ SDK_PRI char pad_0x9[0x1];
	/* 0x000A */ SDK_PUB bool m_bGuiHidden;
	/* 0x000B */ SDK_PUB bool m_bForceGuiHidden;
	/* 0x000C */ SDK_PRI bool m_bPrevForceGuiHidden;
	/* 0x000D */ SDK_PRI char pad_0xD[0x3];
	/* 0x0010 */ SDK_PUB std::shared_ptr<class InGameMainMenu2> m_pMainMenu;
	/* 0x0020 */ SDK_PUB std::shared_ptr<class HudGui2> m_pHudGui;
	/* 0x0030 */ SDK_PUB std::shared_ptr<class InventoryGui> m_pInventory;
	/* 0x0040 */ SDK_PUB std::shared_ptr<class ContainerGui2> m_pContainerGui;
	/* 0x0050 */ SDK_PUB std::shared_ptr<class ChatGui> m_pChatGui;
	/* 0x0060 */ SDK_PUB std::shared_ptr<class LiftGui> m_pLiftGui;
	/* 0x0070 */ SDK_PUB std::shared_ptr<class PaintToolGui> m_pPaintToolGui;
	/* 0x0080 */ SDK_PUB std::shared_ptr<class HandbookGui> m_pHandbookGui;
	/* 0x0090 */ SDK_PUB std::shared_ptr<class InteractableEngineGui> m_pInteractableEngineGui;
	/* 0x00A0 */ SDK_PUB std::shared_ptr<class InteractableSeatGui> m_pInteractableSeatGui;
	/* 0x00B0 */ SDK_PUB std::shared_ptr<class InteractableLightGui> m_pInteractableLightGui;
	/* 0x00C0 */ SDK_PUB std::shared_ptr<class InteractablePistonGui> m_pInteractablePistonGui;
	/* 0x00D0 */ SDK_PUB std::shared_ptr<class InteractableLogicGui> m_pInteractableLogicGui;
	/* 0x00E0 */ SDK_PUB std::shared_ptr<class InteractableSequenceGui> m_pInteractableSequenceGui;
	/* 0x00F0 */ SDK_PUB std::shared_ptr<class InteractableTimerGui> m_pInteractableTimerGui;
	/* 0x0100 */ SDK_PUB std::shared_ptr<class InteractableCameraGui> m_pInteractableCameraGui;
	/* 0x0110 */ SDK_PUB std::shared_ptr<class InteractableSensorGui> m_pInteractableSensorGui;
	/* 0x0120 */ SDK_PUB std::shared_ptr<class InteractableToneGui> m_pInteractableToneGui;
	/* 0x0130 */ SDK_PUB std::vector<std::shared_ptr<class GuiBase>> m_pMainGuiLayouts;
	/* 0x0148 */ SDK_PUB std::vector<std::shared_ptr<class LuaGuiInterface>> m_vecLuaGuiInterfaces2;
	/* 0x0160 */ SDK_PUB std::vector<std::shared_ptr<class LuaGuiInterface>> m_vecLuaGuiInterfaces;
	/* 0x0178 */ SDK_PUB std::vector<std::shared_ptr<class GuiInterface>> m_vecGuiInterfaces;
	/* 0x0190 */ SDK_PRI char pad_0x190[0x18];
	/* 0x01A8 */ SDK_PUB std::shared_ptr<GuiBase> m_pActiveGuiObject;
	/* 0x01B8 */ SDK_PUB std::vector<std::shared_ptr<GuiBase>> m_vecActiveGuiObjects;
	/* 0x01D0 */ SDK_PUB struct DynamicShapeGroup* m_pDynamicShapeGroup;
	/* 0x01D8 */ SDK_PUB struct DynamicShapeRenderSystem* m_pDynShapeRenderSystem;
	/* 0x01E0 */ SDK_PRI char pad_0x1E0[0x10];
}; // Size: 0x1F0

static_assert(offsetof(InGameGuiManager, InGameGuiManager::m_bDefaultGuisInitialized) == 0x8, "InGameGuiManager::m_bDefaultGuisInitialized: Incorrect offset");
static_assert(offsetof(InGameGuiManager, InGameGuiManager::m_bGuiHidden) == 0xA, "InGameGuiManager::m_bGuiHidden: Incorrect offset");
static_assert(offsetof(InGameGuiManager, InGameGuiManager::m_bForceGuiHidden) == 0xB, "InGameGuiManager::m_bForceGuiHidden: Incorrect offset");
static_assert(offsetof(InGameGuiManager, InGameGuiManager::m_pMainMenu) == 0x10, "InGameGuiManager::m_pMainMenu: Incorrect offset");
static_assert(offsetof(InGameGuiManager, InGameGuiManager::m_pHudGui) == 0x20, "InGameGuiManager::m_pHudGui: Incorrect offset");
static_assert(offsetof(InGameGuiManager, InGameGuiManager::m_pInventory) == 0x30, "InGameGuiManager::m_pInventory: Incorrect offset");
static_assert(offsetof(InGameGuiManager, InGameGuiManager::m_pContainerGui) == 0x40, "InGameGuiManager::m_pContainerGui: Incorrect offset");
static_assert(offsetof(InGameGuiManager, InGameGuiManager::m_pChatGui) == 0x50, "InGameGuiManager::m_pChatGui: Incorrect offset");
static_assert(offsetof(InGameGuiManager, InGameGuiManager::m_pLiftGui) == 0x60, "InGameGuiManager::m_pLiftGui: Incorrect offset");
static_assert(offsetof(InGameGuiManager, InGameGuiManager::m_pPaintToolGui) == 0x70, "InGameGuiManager::m_pPaintToolGui: Incorrect offset");
static_assert(offsetof(InGameGuiManager, InGameGuiManager::m_pHandbookGui) == 0x80, "InGameGuiManager::m_pHandbookGui: Incorrect offset");
static_assert(offsetof(InGameGuiManager, InGameGuiManager::m_pInteractableEngineGui) == 0x90, "InGameGuiManager::m_pInteractableEngineGui: Incorrect offset");
static_assert(offsetof(InGameGuiManager, InGameGuiManager::m_pInteractableSeatGui) == 0xA0, "InGameGuiManager::m_pInteractableSeatGui: Incorrect offset");
static_assert(offsetof(InGameGuiManager, InGameGuiManager::m_pInteractableLightGui) == 0xB0, "InGameGuiManager::m_pInteractableLightGui: Incorrect offset");
static_assert(offsetof(InGameGuiManager, InGameGuiManager::m_pInteractablePistonGui) == 0xC0, "InGameGuiManager::m_pInteractablePistonGui: Incorrect offset");
static_assert(offsetof(InGameGuiManager, InGameGuiManager::m_pInteractableLogicGui) == 0xD0, "InGameGuiManager::m_pInteractableLogicGui: Incorrect offset");
static_assert(offsetof(InGameGuiManager, InGameGuiManager::m_pInteractableSequenceGui) == 0xE0, "InGameGuiManager::m_pInteractableSequenceGui: Incorrect offset");
static_assert(offsetof(InGameGuiManager, InGameGuiManager::m_pInteractableTimerGui) == 0xF0, "InGameGuiManager::m_pInteractableTimerGui: Incorrect offset");
static_assert(offsetof(InGameGuiManager, InGameGuiManager::m_pInteractableCameraGui) == 0x100, "InGameGuiManager::m_pInteractableCameraGui: Incorrect offset");
static_assert(offsetof(InGameGuiManager, InGameGuiManager::m_pInteractableSensorGui) == 0x110, "InGameGuiManager::m_pInteractableSensorGui: Incorrect offset");
static_assert(offsetof(InGameGuiManager, InGameGuiManager::m_pInteractableToneGui) == 0x120, "InGameGuiManager::m_pInteractableToneGui: Incorrect offset");
static_assert(offsetof(InGameGuiManager, InGameGuiManager::m_pMainGuiLayouts) == 0x130, "InGameGuiManager::m_pMainGuiLayouts: Incorrect offset");
static_assert(offsetof(InGameGuiManager, InGameGuiManager::m_vecLuaGuiInterfaces2) == 0x148, "InGameGuiManager::m_vecLuaGuiInterfaces2: Incorrect offset");
static_assert(offsetof(InGameGuiManager, InGameGuiManager::m_vecLuaGuiInterfaces) == 0x160, "InGameGuiManager::m_vecLuaGuiInterfaces: Incorrect offset");
static_assert(offsetof(InGameGuiManager, InGameGuiManager::m_vecGuiInterfaces) == 0x178, "InGameGuiManager::m_vecGuiInterfaces: Incorrect offset");
static_assert(offsetof(InGameGuiManager, InGameGuiManager::m_pActiveGuiObject) == 0x1A8, "InGameGuiManager::m_pActiveGuiObject: Incorrect offset");
static_assert(offsetof(InGameGuiManager, InGameGuiManager::m_vecActiveGuiObjects) == 0x1B8, "InGameGuiManager::m_vecActiveGuiObjects: Incorrect offset");
static_assert(offsetof(InGameGuiManager, InGameGuiManager::m_pDynamicShapeGroup) == 0x1D0, "InGameGuiManager::m_pDynamicShapeGroup: Incorrect offset");
static_assert(offsetof(InGameGuiManager, InGameGuiManager::m_pDynShapeRenderSystem) == 0x1D8, "InGameGuiManager::m_pDynShapeRenderSystem: Incorrect offset");

static_assert(sizeof(InGameGuiManager) == 0x1F0, "InGameGuiManager: Incorrect Size");

SMSDK_END_NAMESPACE