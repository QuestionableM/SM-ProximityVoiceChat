#pragma once

#include "SmSdk/mygui_include.hpp"
#include "SmSdk/config.hpp"

SMSDK_BEGIN_NAMESPACE

class VerticalStackBox
{
#if defined(SMSDK_ENABLE_MYGUI) || defined(SMSDK_BUILD_DLL) || defined(SMSDK_IMPORT_DLL)
	SDK_PUB SMSDK_API VerticalStackBox(MyGUI::IntSize itemSz);

	SDK_PUB SMSDK_API void onParentChangeCoord(MyGUI::Widget* pCaller);
	SDK_PUB SMSDK_API void onPanelScroll(MyGUI::Widget* pCaller, int iScrollVal);
	SDK_PUB SMSDK_API void onScrollbarChangePosition(MyGUI::ScrollBar* pCaller, size_t uPos);
	SDK_PUB SMSDK_API void initialize(MyGUI::Widget* pParent, MyGUI::ScrollBar* pScrollBar);

	SDK_PUB SMSDK_API void onItemChangeCoord(MyGUI::Widget* pCaller);
	SDK_PUB SMSDK_API void onItemScroll(MyGUI::Widget* pCaller, int iScrollVal);
	SDK_PUB SMSDK_API void updateScrollBar();
	SDK_PUB SMSDK_API MyGUI::Widget* createNewOption();
	SDK_PUB SMSDK_API void clearItems();
#endif

	/* 0x0000 */ SDK_MEM_PUB MyGUI::IntSize m_itemSize;
	/* 0x0008 */ SDK_MEM_PUB std::string m_skin;
	/* 0x0028 */ SDK_MEM_PUB MyGUI::Widget* m_pParent;
	/* 0x0030 */ SDK_MEM_PUB MyGUI::Widget* m_pEmptyPanel;
	/* 0x0038 */ SDK_MEM_PUB MyGUI::ScrollBar* m_pScrollBar;
	/* 0x0040 */ SDK_MEM_PUB bool m_bEnableSeparators;
	/* 0x0041 */ SDK_MEM_PRI char pad_0x41[0x3];
	/* 0x0044 */ SDK_MEM_PRI std::int32_t m_iSomeVal3;
	/* 0x0048 */ SDK_MEM_PRI std::int32_t m_iSomeVal4;
	/* 0x004C */ SDK_MEM_PUB std::int32_t m_iScrollDistance;
	/* 0x0050 */ SDK_MEM_PUB std::int32_t m_iScrollValue;
	/* 0x0054 */ SDK_MEM_PRI std::int32_t m_iSomeVal7;
	/* 0x0058 */ SDK_MEM_PUB MyGUI::IntPoint m_panelPos;
	/* 0x0060 */ SDK_MEM_PUB std::vector<MyGUI::Widget*> m_vecWidgets;
	/* 0x0078 */ SDK_MEM_PUB MyGUI::Colour m_separatorColor;
}; // Size: 0x88

SMSDK_CHECK_MEMBER_OFFSET(VerticalStackBox, m_itemSize, 0x0);
SMSDK_CHECK_MEMBER_OFFSET(VerticalStackBox, m_skin, 0x8);
SMSDK_CHECK_MEMBER_OFFSET(VerticalStackBox, m_pParent, 0x28);
SMSDK_CHECK_MEMBER_OFFSET(VerticalStackBox, m_pEmptyPanel, 0x30);
SMSDK_CHECK_MEMBER_OFFSET(VerticalStackBox, m_pScrollBar, 0x38);
SMSDK_CHECK_MEMBER_OFFSET(VerticalStackBox, m_bEnableSeparators, 0x40);
SMSDK_CHECK_MEMBER_OFFSET(VerticalStackBox, m_iScrollDistance, 0x4C);
SMSDK_CHECK_MEMBER_OFFSET(VerticalStackBox, m_iScrollValue, 0x50);
SMSDK_CHECK_MEMBER_OFFSET(VerticalStackBox, m_panelPos, 0x58);
SMSDK_CHECK_MEMBER_OFFSET(VerticalStackBox, m_vecWidgets, 0x60);
SMSDK_CHECK_MEMBER_OFFSET(VerticalStackBox, m_separatorColor, 0x78);
SMSDK_CHECK_STRUCT_SIZE(VerticalStackBox, 0x88);

SMSDK_END_NAMESPACE