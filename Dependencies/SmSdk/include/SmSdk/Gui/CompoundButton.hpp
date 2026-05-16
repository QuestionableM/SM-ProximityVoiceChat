#pragma once

#include "SmSdk/mygui_include.hpp"

#include "SmSdk/Util/Memory.hpp"
#include "SmSdk/offsets.hpp"

SMSDK_BEGIN_NAMESPACE

class CompoundButton
{
	// Version independent constructor
	SDK_PUB SMSDK_API static std::shared_ptr<CompoundButton> New(MyGUI::Widget* pBaseWidget);
	// Version dependent constructor
	SDK_PUB SMSDK_API CompoundButton(MyGUI::Widget* pBaseWidget);

	SDK_PUB SMSDK_API static void setColorInherited(MyGUI::Widget* pWidget, const MyGUI::Colour& color);
	SDK_PUB SMSDK_API void update();

	SDK_PUB SMSDK_API void mouseSetFocusCallback(MyGUI::Widget* _sender, MyGUI::Widget* _old);
	SDK_PUB SMSDK_API void mouseLostFocusCallback(MyGUI::Widget* _sender, MyGUI::Widget* _new);

	SDK_PUB SMSDK_API void mouseButtonPressedCallback(MyGUI::Widget* _sender, const int _left, const int _top, const MyGUI::MouseButton _id);
	SDK_PUB SMSDK_API void mouseButtonReleasedCallback(MyGUI::Widget* _sender, const int _left, const int _top, const MyGUI::MouseButton _id);

	SDK_PUB SMSDK_API void mouseButtonClickCallback(MyGUI::Widget* _sender);

	/* 0x0000 */ SDK_PUB MyGUI::Widget* m_pBaseWidget;
	/* 0x0008 */ SDK_PUB MyGUI::Button* m_pButton;
}; // Size: 0x10

static_assert(offsetof(CompoundButton, CompoundButton::m_pBaseWidget) == 0x0, "CompoundButton::m_pBaseWidget: Incorrect offset");
static_assert(offsetof(CompoundButton, CompoundButton::m_pButton) == 0x8, "CompoundButton::m_pButton: Incorrect offset");
static_assert(sizeof(CompoundButton) == 0x10, "CompoundButton: Incorrect Size");

SMSDK_END_NAMESPACE