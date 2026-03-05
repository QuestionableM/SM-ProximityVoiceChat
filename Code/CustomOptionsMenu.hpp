#pragma once

#include <SmSdk/Gui/OptionsMenu.hpp>

class CustomOptionsMenu : public SM::OptionsMenu
{
public:
	using fConstructor = SM::OptionsMenu* (*)(OptionsMenu*, SM::MainMenuRootGui*, bool);
	using fInitialize = void (*)(OptionsMenu*);

	static fConstructor o_Constructor;
	static OptionsMenu* h_Constructor(OptionsMenu* self, SM::MainMenuRootGui* root_gui, bool is_server);

	static fInitialize o_Initialize;
	static void h_Initialize(OptionsMenu* self);

	void backPanelMouseClick(MyGUI::Widget* widget);
	void defaultButtonClick(MyGUI::Widget* widget);
	void switchTabCallback(MyGUI::Widget* widget);
};