#pragma once

#include <SmSdk/Util/Memory.hpp>
#include <SmSdk/offsets.hpp>

#include <MyGUI.h>
#include <vector>

class VerticalStackBox
{
public:
	MyGUI::Widget* createNewOption();

private:
	/* 0x0000 */ char pad_0x0[0x8];
public:
	/* 0x0008 */ std::string skin;
private:
	/* 0x0028 */ char pad_0x28[0x38];
public:
	/* 0x0060 */ std::vector<MyGUI::Widget*> widgets;
	/* 0x0078 */ MyGUI::Colour color;
}; // Size: 0x88

static_assert(offsetof(VerticalStackBox, VerticalStackBox::skin) == 0x8, "VerticalStackBox::skin: Incorrect offset");
static_assert(offsetof(VerticalStackBox, VerticalStackBox::widgets) == 0x60, "VerticalStackBox::widgets: Incorrect offset");
static_assert(offsetof(VerticalStackBox, VerticalStackBox::color) == 0x78, "VerticalStackBox::color: Incorrect offset");

static_assert(sizeof(VerticalStackBox) == 0x88, "VerticalStackBox: Incorrect Size");


class OptionsSubMenuBase
{
public:
	static void GameConstructor(OptionsSubMenuBase* self)
	{
		using fSubMenuBaseConstructor = void (*)(OptionsSubMenuBase*);
		Memory::Read<fSubMenuBaseConstructor>(SM_CONSTRUCTOR_OPTIONS_SUB_MENU_BASE_OFFSET)(self);
	}

	virtual ~OptionsSubMenuBase() = default;
	virtual void initialize(MyGUI::Widget* parent) { /* implemented by the game */ }
	virtual void cleanSomething() { /* implemented by the game */ }
	virtual void openMenu() { /* implemented by the game */ }
	virtual void closeMenu() { /* implemented by the game */ }

	virtual void onUpdate() { /* implemented by the game */ }
	virtual bool someFunc2() { return 0; }
	virtual bool someFunc3() { return 0; }
	virtual void restoreDefaults() {}
	virtual void someFunc4() { /* implemented by the game */ }

public:
	/* 0x0008 */ MyGUI::Widget* m_pSubMenuWidget;
	/* 0x0010 */ MyGUI::Widget* m_pContainerHostPanel;
	/* 0x0018 */ MyGUI::Widget* m_pContainer;
	/* 0x0020 */ MyGUI::ScrollBar* m_pScrollBar;
private:
	/* 0x0028 */ char pad_0x28[0x8];
public:
	/* 0x0030 */ VerticalStackBox options1;
	/* 0x00B8 */ VerticalStackBox options2;
private:
	/* 0x0140 */ char pad_0x140[0x28];
}; // Size: 0x168

static_assert(offsetof(OptionsSubMenuBase, OptionsSubMenuBase::m_pSubMenuWidget) == 0x8, "OptionsSubMenuBase::m_pSubMenuWidget: Incorrect offset");
static_assert(offsetof(OptionsSubMenuBase, OptionsSubMenuBase::m_pContainerHostPanel) == 0x10, "OptionsSubMenuBase::m_pContainerHostPanel: Incorrect offset");
static_assert(offsetof(OptionsSubMenuBase, OptionsSubMenuBase::m_pContainer) == 0x18, "OptionsSubMenuBase::m_pContainer: Incorrect offset");
static_assert(offsetof(OptionsSubMenuBase, OptionsSubMenuBase::m_pScrollBar) == 0x20, "OptionsSubMenuBase::m_pScrollBar: Incorrect offset");
static_assert(offsetof(OptionsSubMenuBase, OptionsSubMenuBase::options1) == 0x30, "OptionsSubMenuBase::options1: Incorrect offset");
static_assert(offsetof(OptionsSubMenuBase, OptionsSubMenuBase::options2) == 0xB8, "OptionsSubMenuBase::options2: Incorrect offset");

static_assert(sizeof(OptionsSubMenuBase) == 0x168, "OptionsSubMenuBase: Incorrect Size");