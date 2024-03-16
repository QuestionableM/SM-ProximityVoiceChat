#pragma once

#include <SmSdk/Gui/OptionsSubMenuBase.hpp>

class VoiceChatSettingsTab : public OptionsSubMenuBase
{
public:
	VoiceChatSettingsTab();
	virtual ~VoiceChatSettingsTab() = default;

	virtual void initialize(MyGUI::Widget* parent) override;
	virtual void cleanSomething() override;
	virtual void openMenu() override;
	virtual void closeMenu() override;

	virtual void onUpdate() override;
	virtual void restoreDefaults() override;
	virtual void someFunc4() override;

	static void InitializeTab(VoiceChatSettingsTab* self, MyGUI::Widget* parent);
};