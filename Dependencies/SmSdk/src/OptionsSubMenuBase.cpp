#include "SmSdk/Gui/OptionsSubMenuBase.hpp"

MyGUI::Widget* VerticalStackBox::createNewOption()
{
	using NewOptionConstructor = MyGUI::Widget* (*)(VerticalStackBox*);
	NewOptionConstructor v_constructor = Memory::Read<NewOptionConstructor>(
		SM_FUNC_VERTICAL_STACK_BOX_ADD_NEW_ITEM_OFFSET);

	return v_constructor(this);
}