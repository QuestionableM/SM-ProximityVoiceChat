#pragma once

#include "SmSdk/Util/Memory.hpp"

#include "SmSdk/mygui_include.hpp"
#include "SmSdk/offsets.hpp"

#include <functional>
#include <vector>

SMSDK_BEGIN_NAMESPACE

class RadioButtonSet
{
	SDK_PUB SMSDK_API RadioButtonSet(const std::vector<MyGUI::Button*>& vecButtons, const std::function<void(MyGUI::Widget*)>& clickCallback);

	SDK_PUB SMSDK_API static std::shared_ptr<RadioButtonSet> New(const std::vector<MyGUI::Button*>& vecButtons, const std::function<void(MyGUI::Widget*)>& clickCallback);
	SDK_PUB SMSDK_API static std::shared_ptr<RadioButtonSet> New(const std::vector<MyGUI::Button*>& vecButtons);

	SDK_PUB SMSDK_API static void ChangeButtonState(MyGUI::Button* pButton, const bool newState);
	SDK_PUB SMSDK_API void updateSelection();

	SDK_PUB SMSDK_API void onItemMouseClick(MyGUI::Widget* _sender);

	/* 0x0000 */ SDK_MEM_PUB MyGUI::Button* m_pSelectedButton;
	/* 0x0008 */ SDK_MEM_PUB std::vector<MyGUI::Button*> m_vecButtons;
	/* 0x0020 */ SDK_MEM_PUB std::function<void(MyGUI::Widget*)> m_pClickCallback;
}; // Size: 0x60

SMSDK_CHECK_MEMBER_OFFSET(RadioButtonSet, m_pSelectedButton, 0x0);
SMSDK_CHECK_MEMBER_OFFSET(RadioButtonSet, m_vecButtons, 0x8);
SMSDK_CHECK_MEMBER_OFFSET(RadioButtonSet, m_pClickCallback, 0x20);
SMSDK_CHECK_STRUCT_SIZE(RadioButtonSet, 0x60);

SMSDK_END_NAMESPACE