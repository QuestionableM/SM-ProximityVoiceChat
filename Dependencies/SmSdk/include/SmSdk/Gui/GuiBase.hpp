#pragma once

#include "SmSdk/unreferenced_params.hpp"
#include "SmSdk/mygui_include.hpp"

#include "SmSdk/Gui/GuiInterface.hpp"

SMSDK_BEGIN_NAMESPACE

class GuiBase
{
	SDK_PUB SMSDK_API GuiBase();
	
	SDK_PUB virtual ~GuiBase() = default;
	SDK_PUB virtual void initialize();
	SDK_PUB virtual void destroyWidgets();
	SDK_PUB virtual void open();
	SDK_PUB virtual void close();
	SDK_PUB virtual bool isActive();
	SDK_PUB virtual void setFocus(const std::string& widget);

	SDK_PUB SMSDK_API MyGUI::Widget* getMainPanel();

	/* 0x0008 */ SDK_PUB MyGUI::Widget* m_pMainPanel;
	/* 0x0010 */ SDK_PUB GuiInterface* m_pGuiInterface;
}; // Size: 0x18

static_assert(sizeof(GuiBase) == 0x18, "GuiBase: Incorrect Size");

SMSDK_END_NAMESPACE