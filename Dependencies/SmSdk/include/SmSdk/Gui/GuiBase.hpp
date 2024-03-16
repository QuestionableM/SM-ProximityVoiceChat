#pragma once

#include "GuiInterface.hpp"
#include "MyGUI.h"

class GuiBase
{
public:
	virtual ~GuiBase() = default;

	virtual void initialize() { /* implemented by the game */ }
	virtual void destroyWidgets() { /* implemented by the game */ }
	virtual void open() { /* implemented by the game */ }
	virtual void close() { /* implemented by the game */ }
	virtual bool isActive() { return m_pMainPanel && m_pMainPanel->getVisible(); }
	virtual void setFocus(const std::string& widget) { /* implemented by the game */ }

	/* 0x0008 */ MyGUI::Widget* m_pMainPanel;
	/* 0x0010 */ GuiInterface* m_pGuiInterface;

}; // Size: 0x18