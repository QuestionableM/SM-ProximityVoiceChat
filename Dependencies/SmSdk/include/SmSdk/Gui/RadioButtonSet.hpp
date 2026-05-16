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

	/* 0x0000 */ SDK_PUB MyGUI::Button* m_pSelectedButton;
	/* 0x0008 */ SDK_PUB std::vector<MyGUI::Button*> m_vecButtons;
	/* 0x0020 */ SDK_PUB std::function<void(MyGUI::Widget*)> m_pClickCallback;

}; // Size: 0x60

static_assert(offsetof(RadioButtonSet, RadioButtonSet::m_pSelectedButton) == 0x0, "RadioButtonSet::m_pSelectedButton: Incorrect offset");
static_assert(offsetof(RadioButtonSet, RadioButtonSet::m_vecButtons) == 0x8, "RadioButtonSet::m_vecButtons: Incorrect offset");
static_assert(offsetof(RadioButtonSet, RadioButtonSet::m_pClickCallback) == 0x20, "RadioButtonSet::m_pCallback: Incorrect offset");

static_assert(sizeof(RadioButtonSet) == 0x60, "RadioButtonSet: Incorrect Size");

SMSDK_END_NAMESPACE