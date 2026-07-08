#pragma once

#include "SmSdk/mygui_include.hpp"
#include "SmSdk/Gui/GuiBase.hpp"

SMSDK_BEGIN_NAMESPACE

class PaintToolGui : public GuiBase
{
	/* 0x0018 */ SDK_MEM_PUB MyGUI::ItemBox* m_pItemBox;
}; // Size: 0x20

SMSDK_CHECK_MEMBER_OFFSET(PaintToolGui, m_pItemBox, 0x18);
SMSDK_CHECK_STRUCT_SIZE(PaintToolGui, 0x20);

SMSDK_END_NAMESPACE