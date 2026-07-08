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

	/* 0x0000 */ SDK_MEM_PUB MyGUI::Widget* m_pBaseWidget;
	/* 0x0008 */ SDK_MEM_PUB MyGUI::Button* m_pButton;
}; // Size: 0x10

SMSDK_CHECK_MEMBER_OFFSET(CompoundButton, m_pBaseWidget, 0x0);
SMSDK_CHECK_MEMBER_OFFSET(CompoundButton, m_pButton, 0x8);
SMSDK_CHECK_STRUCT_SIZE(CompoundButton, 0x10);

SMSDK_END_NAMESPACE