#pragma once

#include "SmSdk/Gui/CompoundButton.hpp"
#include "SmSdk/Gui/GuiBase.hpp"

SMSDK_BEGIN_NAMESPACE

class MainMenuRootGui : public GuiBase
{
	/* 0x0018 */ SDK_MEM_PRI char pad_0x18[0x8];
	/* 0x0020 */ SDK_MEM_PUB struct MenuState* m_pMenuState;
	/* 0x0028 */ SDK_MEM_PRI char pad_0x28[0x10];
	/* 0x0038 */ SDK_MEM_PUB std::vector<std::shared_ptr<CompoundButton>> m_vecCompoundButtons;
	/* 0x0050 */ SDK_MEM_PUB std::vector<GuiBase*> m_vecGuis;
	/* 0x0068 */ SDK_MEM_PUB GuiBase* m_pCurrentGuiElement;
	/* 0x0070 */ SDK_MEM_PUB struct ChooseGameModeMenu* m_pChooseGameModeMenu;
	/* 0x0078 */ SDK_MEM_PUB struct CreativeModeMenu* m_pCreativeModeMenu;
	/* 0x0080 */ SDK_MEM_PUB struct SurvivalModeMenu* m_pSurvivalModeMenu;
	/* 0x0088 */ SDK_MEM_PUB struct ChallengeModeMenu* m_pChallengeModeMenu;
	/* 0x0090 */ SDK_MEM_PUB struct CustomGameModeMenu* m_pCustomGameModeMenu;
	/* 0x0098 */ SDK_MEM_PUB struct CharacterCustomizationMenu* m_pCharacterCustomizationMenu;
	/* 0x00A0 */ SDK_MEM_PUB class OptionsMenu* m_pOptionsMenu;
}; // Size: 0xA8

SMSDK_CHECK_MEMBER_OFFSET(MainMenuRootGui, m_pMenuState, 0x20);
SMSDK_CHECK_MEMBER_OFFSET(MainMenuRootGui, m_vecCompoundButtons, 0x38);
SMSDK_CHECK_MEMBER_OFFSET(MainMenuRootGui, m_vecGuis, 0x50);
SMSDK_CHECK_MEMBER_OFFSET(MainMenuRootGui, m_pCurrentGuiElement, 0x68);
SMSDK_CHECK_MEMBER_OFFSET(MainMenuRootGui, m_pChooseGameModeMenu, 0x70);
SMSDK_CHECK_MEMBER_OFFSET(MainMenuRootGui, m_pCreativeModeMenu, 0x78);
SMSDK_CHECK_MEMBER_OFFSET(MainMenuRootGui, m_pSurvivalModeMenu, 0x80);
SMSDK_CHECK_MEMBER_OFFSET(MainMenuRootGui, m_pChallengeModeMenu, 0x88);
SMSDK_CHECK_MEMBER_OFFSET(MainMenuRootGui, m_pCustomGameModeMenu, 0x90);
SMSDK_CHECK_MEMBER_OFFSET(MainMenuRootGui, m_pCharacterCustomizationMenu, 0x98);
SMSDK_CHECK_MEMBER_OFFSET(MainMenuRootGui, m_pOptionsMenu, 0xA0);
SMSDK_CHECK_STRUCT_SIZE(MainMenuRootGui, 0xA8);

SMSDK_END_NAMESPACE