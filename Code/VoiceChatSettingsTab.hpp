#pragma once

#include <SmSdk/Gui/OptionsSubMenuBase.hpp>

#include <unordered_set>

class VoiceChatSettingsTab : public OptionsSubMenuBase
{
public:
	VoiceChatSettingsTab();
	virtual ~VoiceChatSettingsTab() = default;

	virtual void initialize(MyGUI::Widget* parent) override;
	virtual void openMenu() override;
	virtual void closeMenu() override;

	bool shouldUpdateVoices();

	virtual void onUpdate() override;
	virtual void restoreDefaults() override;
	virtual void someFunc4() override;

public:
	std::unordered_set<int> m_registeredVoices;
	//A text that appears when there's no players
	MyGUI::TextBox* m_pEmptyListText;
};