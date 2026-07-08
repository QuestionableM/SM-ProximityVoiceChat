#pragma once

#include "SmSdk/unreferenced_params.hpp"
#include "SmSdk/mygui_include.hpp"
#include "SmSdk/Util/Memory.hpp"
#include "SmSdk/offsets.hpp"

#include "SmSdk/Gui/VerticalStackBox.hpp"
#include "SmSdk/Gui/OptionsItemBase.hpp"

#include <vector>

SMSDK_BEGIN_NAMESPACE

class OptionsSubMenuBase
{
#if defined(SMSDK_ENABLE_MYGUI) || defined(SMSDK_BUILD_DLL) || defined(SMSDK_IMPORT_DLL)
	SDK_PRO SMSDK_API OptionsSubMenuBase();

	SDK_PUB SMSDK_API void onScrollChangePos(MyGUI::ScrollBar* pCaller, size_t iPos);
	SDK_PUB SMSDK_API void onScroll(MyGUI::Widget* pCaller, int iScrollVal);
	SDK_PUB SMSDK_API void updateScrollArea();
	SDK_PUB SMSDK_API void updateScrollAreaAndScrollBar();
	SDK_PUB SMSDK_API void clear(const bool clearScrollBar);
#endif

	SDK_PUB SMSDK_API MyGUI::Widget* getSubMenuWidget();
	SDK_PUB SMSDK_API VerticalStackBox* getLeftStackBox();
	SDK_PUB SMSDK_API VerticalStackBox* getRightStackBox();
	SDK_PUB SMSDK_API void addOptionItem(const std::shared_ptr<OptionsItemBase>& item);

	SDK_PUB SMSDK_API virtual ~OptionsSubMenuBase() = default;

	SDK_PUB SMSDK_API virtual void initialize(MyGUI::Widget* pParent) DEFAULT_IMPL_UNREF(pParent);

	SDK_PUB SMSDK_API virtual void cleanOptionItems() DEFAULT_IMPL();
	SDK_PUB SMSDK_API virtual void openMenu() DEFAULT_IMPL();
	SDK_PUB SMSDK_API virtual void closeMenu() DEFAULT_IMPL();

	SDK_PUB SMSDK_API virtual void onUpdate() {}

	SDK_PRI SMSDK_API virtual bool someFunc2() { return 0; }
	SDK_PRI SMSDK_API virtual bool someFunc3() { return 0; }
	SDK_PUB SMSDK_API virtual void restoreDefaults() = 0;

#if _SM_VERSION_NUM >= 070771
	SDK_PRI SMSDK_API virtual void someFunc5() {}
#endif
	SDK_PRI SMSDK_API virtual void someFunc4() {}

	/* 0x0008 */ SDK_MEM_PUB MyGUI::Widget* m_pSubMenuWidget;
	/* 0x0010 */ SDK_MEM_PUB MyGUI::Widget* m_pContainerHostPanel;
	/* 0x0018 */ SDK_MEM_PUB MyGUI::Widget* m_pContainer;
	/* 0x0020 */ SDK_MEM_PUB MyGUI::ScrollBar* m_pScrollBar;
	/* 0x0028 */ SDK_MEM_PUB MyGUI::IntSize m_itemSize;
	/* 0x0030 */ SDK_MEM_PUB VerticalStackBox m_leftStackBox;
	/* 0x00B8 */ SDK_MEM_PUB VerticalStackBox m_rightStackBox;
	/* 0x0140 */ SDK_MEM_PUB std::vector<std::shared_ptr<OptionsItemBase>> m_vecOptionItems;
	/* 0x0158 */ SDK_MEM_PUB std::int32_t m_iScrollValue;
	/* 0x015C */ SDK_MEM_PUB MyGUI::IntPoint m_containerPos;
	/* 0x0164 */ SDK_MEM_PRI char pad_0x164[0x4];
}; // Size: 0x168

SMSDK_CHECK_MEMBER_OFFSET(OptionsSubMenuBase, m_pSubMenuWidget, 0x8);
SMSDK_CHECK_MEMBER_OFFSET(OptionsSubMenuBase, m_pContainerHostPanel, 0x10);
SMSDK_CHECK_MEMBER_OFFSET(OptionsSubMenuBase, m_pContainer, 0x18);
SMSDK_CHECK_MEMBER_OFFSET(OptionsSubMenuBase, m_pScrollBar, 0x20);
SMSDK_CHECK_MEMBER_OFFSET(OptionsSubMenuBase, m_itemSize, 0x28);
SMSDK_CHECK_MEMBER_OFFSET(OptionsSubMenuBase, m_leftStackBox, 0x30);
SMSDK_CHECK_MEMBER_OFFSET(OptionsSubMenuBase, m_rightStackBox, 0xB8);
SMSDK_CHECK_MEMBER_OFFSET(OptionsSubMenuBase, m_vecOptionItems, 0x140);
SMSDK_CHECK_MEMBER_OFFSET(OptionsSubMenuBase, m_iScrollValue, 0x158);
SMSDK_CHECK_MEMBER_OFFSET(OptionsSubMenuBase, m_containerPos, 0x15C);
SMSDK_CHECK_STRUCT_SIZE(OptionsSubMenuBase, 0x168);

SMSDK_END_NAMESPACE