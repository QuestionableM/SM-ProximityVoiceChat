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

	/* 0x0008 */ SDK_MEM_PUB bool m_bDefaultGuisInitialized;
	/* 0x0009 */ SDK_MEM_PRI char pad_0x9[0x1];
	/* 0x000A */ SDK_MEM_PUB bool m_bGuiHidden;
	/* 0x000B */ SDK_MEM_PUB bool m_bForceGuiHidden;
	/* 0x000C */ SDK_MEM_PRI bool m_bPrevForceGuiHidden;
	/* 0x000D */ SDK_MEM_PRI char pad_0xD[0x3];
	/* 0x0010 */ SDK_MEM_PUB std::shared_ptr<class InGameMainMenu2> m_pMainMenu;
	/* 0x0020 */ SDK_MEM_PUB std::shared_ptr<class HudGui2> m_pHudGui;
	/* 0x0030 */ SDK_MEM_PUB std::shared_ptr<class InventoryGui> m_pInventory;
	/* 0x0040 */ SDK_MEM_PUB std::shared_ptr<class ContainerGui2> m_pContainerGui;
	/* 0x0050 */ SDK_MEM_PUB std::shared_ptr<class ChatGui> m_pChatGui;
	/* 0x0060 */ SDK_MEM_PUB std::shared_ptr<class LiftGui> m_pLiftGui;
	/* 0x0070 */ SDK_MEM_PUB std::shared_ptr<class PaintToolGui> m_pPaintToolGui;
	/* 0x0080 */ SDK_MEM_PUB std::shared_ptr<class HandbookGui> m_pHandbookGui;
	/* 0x0090 */ SDK_MEM_PUB std::shared_ptr<class InteractableEngineGui> m_pInteractableEngineGui;
	/* 0x00A0 */ SDK_MEM_PUB std::shared_ptr<class InteractableSeatGui> m_pInteractableSeatGui;
	/* 0x00B0 */ SDK_MEM_PUB std::shared_ptr<class InteractableLightGui> m_pInteractableLightGui;
	/* 0x00C0 */ SDK_MEM_PUB std::shared_ptr<class InteractablePistonGui> m_pInteractablePistonGui;
	/* 0x00D0 */ SDK_MEM_PUB std::shared_ptr<class InteractableLogicGui> m_pInteractableLogicGui;
	/* 0x00E0 */ SDK_MEM_PUB std::shared_ptr<class InteractableSequenceGui> m_pInteractableSequenceGui;
	/* 0x00F0 */ SDK_MEM_PUB std::shared_ptr<class InteractableTimerGui> m_pInteractableTimerGui;
	/* 0x0100 */ SDK_MEM_PUB std::shared_ptr<class InteractableCameraGui> m_pInteractableCameraGui;
	/* 0x0110 */ SDK_MEM_PUB std::shared_ptr<class InteractableSensorGui> m_pInteractableSensorGui;
	/* 0x0120 */ SDK_MEM_PUB std::shared_ptr<class InteractableToneGui> m_pInteractableToneGui;
	/* 0x0130 */ SDK_MEM_PUB std::vector<std::shared_ptr<class GuiBase>> m_pMainGuiLayouts;
	/* 0x0148 */ SDK_MEM_PUB std::vector<std::shared_ptr<class LuaGuiInterface>> m_vecLuaGuiInterfaces2;
	/* 0x0160 */ SDK_MEM_PUB std::vector<std::shared_ptr<class LuaGuiInterface>> m_vecLuaGuiInterfaces;
	/* 0x0178 */ SDK_MEM_PUB std::vector<std::shared_ptr<class GuiInterface>> m_vecGuiInterfaces;
	/* 0x0190 */ SDK_MEM_PRI char pad_0x190[0x18];
	/* 0x01A8 */ SDK_MEM_PUB std::shared_ptr<GuiBase> m_pActiveGuiObject;
	/* 0x01B8 */ SDK_MEM_PUB std::vector<std::shared_ptr<GuiBase>> m_vecActiveGuiObjects;
	/* 0x01D0 */ SDK_MEM_PUB struct DynamicShapeGroup* m_pDynamicShapeGroup;
	/* 0x01D8 */ SDK_MEM_PUB struct DynamicShapeRenderSystem* m_pDynShapeRenderSystem;
	/* 0x01E0 */ SDK_MEM_PRI char pad_0x1E0[0x10];
}; // Size: 0x1F0

SMSDK_CHECK_MEMBER_OFFSET(InGameGuiManager, m_bDefaultGuisInitialized, 0x8);
SMSDK_CHECK_MEMBER_OFFSET(InGameGuiManager, m_bGuiHidden, 0xA);
SMSDK_CHECK_MEMBER_OFFSET(InGameGuiManager, m_bForceGuiHidden, 0xB);
SMSDK_CHECK_MEMBER_OFFSET(InGameGuiManager, m_pMainMenu, 0x10);
SMSDK_CHECK_MEMBER_OFFSET(InGameGuiManager, m_pHudGui, 0x20);
SMSDK_CHECK_MEMBER_OFFSET(InGameGuiManager, m_pInventory, 0x30);
SMSDK_CHECK_MEMBER_OFFSET(InGameGuiManager, m_pContainerGui, 0x40);
SMSDK_CHECK_MEMBER_OFFSET(InGameGuiManager, m_pChatGui, 0x50);
SMSDK_CHECK_MEMBER_OFFSET(InGameGuiManager, m_pLiftGui, 0x60);
SMSDK_CHECK_MEMBER_OFFSET(InGameGuiManager, m_pPaintToolGui, 0x70);
SMSDK_CHECK_MEMBER_OFFSET(InGameGuiManager, m_pHandbookGui, 0x80);
SMSDK_CHECK_MEMBER_OFFSET(InGameGuiManager, m_pInteractableEngineGui, 0x90);
SMSDK_CHECK_MEMBER_OFFSET(InGameGuiManager, m_pInteractableSeatGui, 0xA0);
SMSDK_CHECK_MEMBER_OFFSET(InGameGuiManager, m_pInteractableLightGui, 0xB0);
SMSDK_CHECK_MEMBER_OFFSET(InGameGuiManager, m_pInteractablePistonGui, 0xC0);
SMSDK_CHECK_MEMBER_OFFSET(InGameGuiManager, m_pInteractableLogicGui, 0xD0);
SMSDK_CHECK_MEMBER_OFFSET(InGameGuiManager, m_pInteractableSequenceGui, 0xE0);
SMSDK_CHECK_MEMBER_OFFSET(InGameGuiManager, m_pInteractableTimerGui, 0xF0);
SMSDK_CHECK_MEMBER_OFFSET(InGameGuiManager, m_pInteractableCameraGui, 0x100);
SMSDK_CHECK_MEMBER_OFFSET(InGameGuiManager, m_pInteractableSensorGui, 0x110);
SMSDK_CHECK_MEMBER_OFFSET(InGameGuiManager, m_pInteractableToneGui, 0x120);
SMSDK_CHECK_MEMBER_OFFSET(InGameGuiManager, m_pMainGuiLayouts, 0x130);
SMSDK_CHECK_MEMBER_OFFSET(InGameGuiManager, m_vecLuaGuiInterfaces2, 0x148);
SMSDK_CHECK_MEMBER_OFFSET(InGameGuiManager, m_vecLuaGuiInterfaces, 0x160);
SMSDK_CHECK_MEMBER_OFFSET(InGameGuiManager, m_vecGuiInterfaces, 0x178);
SMSDK_CHECK_MEMBER_OFFSET(InGameGuiManager, m_pActiveGuiObject, 0x1A8);
SMSDK_CHECK_MEMBER_OFFSET(InGameGuiManager, m_vecActiveGuiObjects, 0x1B8);
SMSDK_CHECK_MEMBER_OFFSET(InGameGuiManager, m_pDynamicShapeGroup, 0x1D0);
SMSDK_CHECK_MEMBER_OFFSET(InGameGuiManager, m_pDynShapeRenderSystem, 0x1D8);
SMSDK_CHECK_STRUCT_SIZE(InGameGuiManager, 0x1F0);

SMSDK_END_NAMESPACE