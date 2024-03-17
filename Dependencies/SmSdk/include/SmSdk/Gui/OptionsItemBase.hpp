#pragma once

#include <MyGUI.h>

class OptionsItemBase
{
public:
	virtual ~OptionsItemBase() = default;
	virtual void update() = 0;

public:
	/* 0x0008 */ MyGUI::Widget* widget;
}; // Size: 0x10

static_assert(offsetof(OptionsItemBase, OptionsItemBase::widget) == 0x8, "OptionsItemBase::widget: Incorrect offset");

static_assert(sizeof(OptionsItemBase) == 0x10, "OptionsItemBase: Incorrect Size");