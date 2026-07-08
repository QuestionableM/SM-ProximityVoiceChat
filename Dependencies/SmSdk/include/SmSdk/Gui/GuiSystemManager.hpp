#pragma once

#include "SmSdk/mygui_include.hpp"
#include "SmSdk/win_include.hpp"

#include <unordered_map>
#include <string>
#include <vector>
#include <memory>
#include <map>

SMSDK_BEGIN_NAMESPACE

class GuiSystemManager
{
	SDK_PUB SMSDK_API static GuiSystemManager* GetInstance();

	SDK_PUB SMSDK_API static bool IsMouseVisible();

	SDK_PUB SMSDK_API std::int32_t getScreenWidth() const;
	SDK_PUB SMSDK_API std::int32_t getScreenHeight() const;
	SDK_PUB SMSDK_API std::int32_t getScreenLeft() const;
	SDK_PUB SMSDK_API std::int32_t getScreenTop() const;

	SDK_PUB float getOptionItemSize() const
	{
		return float(getScreenHeight()) * (1.0f / 720.0f);
	}

	SDK_PUB float getOptionItemSize2() const
	{
		return float(getScreenHeight()) * (1.0f / 1080.0f);
	}

	// Helper function
	SDK_PUB static int ProcessScroll(
		const int unknownVal,
		const int scrollDistance,
		const int topPos,
		const int scrollVal,
		const float itemSize)
	{
		if (unknownVal <= 0)
			return 0;

		const int vScrollClamped = (scrollVal <= 0)
			? -scrollDistance
			: scrollDistance;

		const int vVal = topPos - int(vScrollClamped * -itemSize);

		return std::min(std::max(-unknownVal, vVal), 0);
	}

	/* 0x0000 */ SDK_MEM_PRI char pad_0x0[0x18];
	/* 0x0018 */ SDK_MEM_PUB std::shared_ptr<MyGUI::DirectX11Platform> m_pMyGUIDx11Platform;
	/* 0x0028 */ SDK_MEM_PUB std::shared_ptr<MyGUI::Gui> m_pGui;
	/* 0x0038 */ SDK_MEM_PUB struct CreateTextureCallback* m_pCreateTextureCallback;
	/* 0x0040 */ SDK_MEM_PUB std::shared_ptr<struct CommonGuiAdditions> m_pCommonGuiAdditions;
	/* 0x0050 */ SDK_MEM_PRI char pad_0x50[0x10];
	/* 0x0060 */ SDK_MEM_PUB std::vector<std::string> m_vecFontNames;
	/* 0x0078 */ SDK_MEM_PUB std::vector<std::string> m_vecFonts;
	/* 0x0090 */ SDK_MEM_PUB std::vector<struct SystemTexture*> m_vecFontTextures;
	/* 0x00A8 */ SDK_MEM_PUB std::unordered_map<std::string, struct SystemTexture*> m_mapFontNameToTexture;
	/* 0x00E8 */ SDK_MEM_PUB std::int32_t m_iScreenWidth;
	/* 0x00EC */ SDK_MEM_PUB std::int32_t m_iScreenHeight;
	/* 0x00F0 */ SDK_MEM_PUB std::int32_t m_iScreenLeft;
	/* 0x00F4 */ SDK_MEM_PUB std::int32_t m_iScreenTop;
	/* 0x00F8 */ SDK_MEM_PUB std::string m_guiLanguage;
	/* 0x0118 */ SDK_MEM_PRI char pad_0x118[0x28];
	/* 0x0140 */ SDK_MEM_PUB std::map<std::string, struct TextureResource*> m_mapPathToTexture;
	/* 0x0150 */ SDK_MEM_PRI char pad_0x150[0x10];
	/* 0x0160 */ SDK_MEM_PUB std::unordered_map<std::string, std::string> m_mapWidgetNameToPath;
	/* 0x01A0 */ SDK_MEM_PUB std::unordered_map<uint8_t, HCURSOR> m_mapCursors;
	/* 0x01E0 */ SDK_MEM_PUB bool m_bMouseState;
	/* 0x01E1 */ SDK_MEM_PUB bool m_bMouseVisible;
	/* 0x01E2 */ SDK_MEM_PRI char pad_0x1E2[0x6];
}; // Size: 0x1E8

SMSDK_CHECK_MEMBER_OFFSET(GuiSystemManager, m_pMyGUIDx11Platform, 0x18);
SMSDK_CHECK_MEMBER_OFFSET(GuiSystemManager, m_pGui, 0x28);
SMSDK_CHECK_MEMBER_OFFSET(GuiSystemManager, m_pCreateTextureCallback, 0x38);
SMSDK_CHECK_MEMBER_OFFSET(GuiSystemManager, m_pCommonGuiAdditions, 0x40);
SMSDK_CHECK_MEMBER_OFFSET(GuiSystemManager, m_vecFontNames, 0x60);
SMSDK_CHECK_MEMBER_OFFSET(GuiSystemManager, m_vecFonts, 0x78);
SMSDK_CHECK_MEMBER_OFFSET(GuiSystemManager, m_vecFontTextures, 0x90);
SMSDK_CHECK_MEMBER_OFFSET(GuiSystemManager, m_mapFontNameToTexture, 0xA8);
SMSDK_CHECK_MEMBER_OFFSET(GuiSystemManager, m_iScreenWidth, 0xE8);
SMSDK_CHECK_MEMBER_OFFSET(GuiSystemManager, m_iScreenHeight, 0xEC);
SMSDK_CHECK_MEMBER_OFFSET(GuiSystemManager, m_iScreenLeft, 0xF0);
SMSDK_CHECK_MEMBER_OFFSET(GuiSystemManager, m_iScreenTop, 0xF4);
SMSDK_CHECK_MEMBER_OFFSET(GuiSystemManager, m_guiLanguage, 0xF8);
SMSDK_CHECK_MEMBER_OFFSET(GuiSystemManager, m_mapPathToTexture, 0x140);
SMSDK_CHECK_MEMBER_OFFSET(GuiSystemManager, m_mapWidgetNameToPath, 0x160);
SMSDK_CHECK_MEMBER_OFFSET(GuiSystemManager, m_mapCursors, 0x1A0);
SMSDK_CHECK_MEMBER_OFFSET(GuiSystemManager, m_bMouseState, 0x1E0);
SMSDK_CHECK_MEMBER_OFFSET(GuiSystemManager, m_bMouseVisible, 0x1E1);
SMSDK_CHECK_STRUCT_SIZE(GuiSystemManager, 0x1E8);

SMSDK_END_NAMESPACE