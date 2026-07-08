#pragma once

#include "SmSdk/mygui_include.hpp"

SMSDK_BEGIN_NAMESPACE

class OptionsItemBase
{
	SDK_PUB SMSDK_API OptionsItemBase();
	
	SDK_PUB virtual ~OptionsItemBase() = default;
	SDK_PUB virtual void update() = 0;

	/* 0x0008 */ SDK_MEM_PUB MyGUI::Widget* m_pBaseWidget;
}; // Size: 0x10

SMSDK_CHECK_MEMBER_OFFSET(OptionsItemBase, m_pBaseWidget, 0x8);
SMSDK_CHECK_STRUCT_SIZE(OptionsItemBase, 0x10);

SMSDK_END_NAMESPACE