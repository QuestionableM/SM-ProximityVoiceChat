#pragma once

#include <MyGUI.h>

class OptionsItemBase
{
private:
	/* 0x0000 */ char pad_0x0[0x8];
public:
	/* 0x0008 */ MyGUI::Widget* widget;
}; // Size: 0x10

static_assert(offsetof(OptionsItemBase, OptionsItemBase::widget) == 0x8, "OptionsItemBase::widget: Incorrect offset");

static_assert(sizeof(OptionsItemBase) == 0x10, "OptionsItemBase: Incorrect Size");