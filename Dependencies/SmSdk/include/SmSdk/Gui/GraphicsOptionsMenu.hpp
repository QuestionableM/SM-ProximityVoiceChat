#pragma once

#include "SmSdk/Gui/OptionsSubMenuBase.hpp"
#include "SmSdk/Util/Memory.hpp"

#include "SmSdk/mygui_include.hpp"
#include "SmSdk/offsets.hpp"

#include <string>

SMSDK_BEGIN_NAMESPACE

struct OptionsItemDropDown;

class GraphicsOptionsMenu : public OptionsSubMenuBase
{
public:
	SDK_PUB SMSDK_API static GraphicsOptionsMenu* New();
	SDK_PRI SMSDK_API GraphicsOptionsMenu();

	virtual ~GraphicsOptionsMenu() = default;
	void restoreDefaults() override { /* implemented by the game */ }

	/* 0x0168 */ SDK_MEM_PRI MyGUI::Button* m_pSomeButton;
	/* 0x0170 */ SDK_MEM_PUB std::shared_ptr<OptionsItemDropDown> m_pShaderQualityDropdown;
	/* 0x0180 */ SDK_MEM_PUB std::shared_ptr<OptionsItemDropDown> m_pReflectionQualityDropdown;
	/* 0x0190 */ SDK_MEM_PUB std::shared_ptr<OptionsItemDropDown> m_pShadowResolutionDropdown;
	/* 0x01A0 */ SDK_MEM_PUB std::shared_ptr<OptionsItemDropDown> m_pShadowQualityDropdown;
	/* 0x01B0 */ SDK_MEM_PUB std::shared_ptr<OptionsItemDropDown> m_pSsaoDropdown;
	/* 0x01C0 */ SDK_MEM_PUB std::shared_ptr<OptionsItemDropDown> m_pFoliageDropdown;
	/* 0x01D0 */ SDK_MEM_PUB std::shared_ptr<OptionsItemDropDown> m_pTextureQualityDropdown;
	/* 0x01E0 */ SDK_MEM_PUB std::shared_ptr<OptionsItemDropDown> m_pDrawDistanceDropdown;
	/* 0x01F0 */ SDK_MEM_PUB std::shared_ptr<OptionsItemDropDown> m_pTexFilteringDropdown;
	/* 0x0200 */ SDK_MEM_PUB std::shared_ptr<OptionsItemDropDown> m_pParticleQualityDropdown;
	/* 0x0210 */ SDK_MEM_PUB std::vector<std::string> m_vecQualityLevelLabels;
	/* 0x0228 */ SDK_MEM_PRI char pad_0x228[0x20];
}; // Size: 0x248

SMSDK_CHECK_MEMBER_OFFSET(GraphicsOptionsMenu, m_pShaderQualityDropdown, 0x170);
SMSDK_CHECK_MEMBER_OFFSET(GraphicsOptionsMenu, m_pReflectionQualityDropdown, 0x180);
SMSDK_CHECK_MEMBER_OFFSET(GraphicsOptionsMenu, m_pShadowResolutionDropdown, 0x190);
SMSDK_CHECK_MEMBER_OFFSET(GraphicsOptionsMenu, m_pShadowQualityDropdown, 0x1A0);
SMSDK_CHECK_MEMBER_OFFSET(GraphicsOptionsMenu, m_pSsaoDropdown, 0x1B0);
SMSDK_CHECK_MEMBER_OFFSET(GraphicsOptionsMenu, m_pFoliageDropdown, 0x1C0);
SMSDK_CHECK_MEMBER_OFFSET(GraphicsOptionsMenu, m_pTextureQualityDropdown, 0x1D0);
SMSDK_CHECK_MEMBER_OFFSET(GraphicsOptionsMenu, m_pDrawDistanceDropdown, 0x1E0);
SMSDK_CHECK_MEMBER_OFFSET(GraphicsOptionsMenu, m_pTexFilteringDropdown, 0x1F0);
SMSDK_CHECK_MEMBER_OFFSET(GraphicsOptionsMenu, m_pParticleQualityDropdown, 0x200);
SMSDK_CHECK_MEMBER_OFFSET(GraphicsOptionsMenu, m_vecQualityLevelLabels, 0x210);
SMSDK_CHECK_STRUCT_SIZE(GraphicsOptionsMenu, 0x248);

SMSDK_END_NAMESPACE