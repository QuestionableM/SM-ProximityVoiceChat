#pragma once

#include <SmSdk/Gui/OptionsMenu.hpp>

class CustomOptionsMenu : public OptionsMenu
{
public:
	using fConstructor = OptionsMenu * (*)(OptionsMenu*, MainMenuRootGui*, bool);
	using fInitialize = void (*)(OptionsMenu*);

	static fConstructor o_Constructor;
	static OptionsMenu* h_Constructor(OptionsMenu* self, MainMenuRootGui* root_gui, bool is_server);

	static fInitialize o_Initialize;
	static void h_Initialize(OptionsMenu* self);

	void backPanelMouseClick(MyGUI::Widget* widget);
	void defaultButtonClick(MyGUI::Widget* widget);
	void switchTabCallback(MyGUI::Widget* widget);
};