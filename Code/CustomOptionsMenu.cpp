#include "CustomOptionsMenu.hpp"

#include <SmSdk/Gui/GraphicsOptionsMenu.hpp>
#include <SmSdk/Gui/GameplayOptionsMenu.hpp>
#include <SmSdk/Gui/ControlOptionsMenu.hpp>
#include <SmSdk/Gui/DisplayOptionsMenu.hpp>
#include <SmSdk/Gui/AudioOptionsMenu.hpp>
#include <SmSdk/Gui/MainMenuRootGui.hpp>

#include <SmSdk/Gui/GuiSystemManager.hpp>
#include <SmSdk/Util/Memory.hpp>
#include <SmSdk/offsets.hpp>

#include "VoiceChatSettingsTab.hpp"
#include "Utils/Console.hpp"

CustomOptionsMenu::fConstructor CustomOptionsMenu::o_Constructor = nullptr;
CustomOptionsMenu::fInitialize CustomOptionsMenu::o_Initialize = nullptr;


OptionsMenu* CustomOptionsMenu::h_Constructor(
	OptionsMenu* self,
	MainMenuRootGui* root_gui,
	bool is_server)
{
	std::memset(self, 0, sizeof(OptionsMenu));
	self = new (self)OptionsMenu;

	Memory::OverwriteVftable(self, SM_VTBL_OPTIONS_MENU_OFFSET);
	self->m_pMenuRootGui = root_gui;
	self->is_server = is_server;

	if (self->is_server)
		self->m_mapSubMenus["Gameplay"] = std::make_shared<GameplayOptionsMenu>();

	self->m_mapSubMenus["Controls"] = std::make_shared<ControlOptionsMenu>();
	self->m_mapSubMenus["Audio"] = std::make_shared<AudioOptionsMenu>();
	self->m_mapSubMenus["Display"] = std::make_shared<DisplayOptionsMenu>();
	self->m_mapSubMenus["Graphics"] = std::make_shared<GraphicsOptionsMenu>();
	self->m_mapSubMenus["ProximityVoiceChat"] = std::make_shared<VoiceChatSettingsTab>();

	self->m_currentTab = self->m_mapSubMenus[self->is_server ? "Gameplay" : "Controls"];
	return self;
}

void CustomOptionsMenu::h_Initialize(OptionsMenu* self)
{
	GuiSystemManager* v_sys_mgr = GuiSystemManager::GetInstance();

	const MyGUI::IntCoord v_panel_coord(
		v_sys_mgr->screen_left, v_sys_mgr->screen_top,
		v_sys_mgr->screen_width, v_sys_mgr->screen_height);

	self->m_pMainPanel = MyGUI::Gui::getInstancePtr()->createWidget<MyGUI::Widget>(
		"PanelEmpty", v_panel_coord, MyGUI::Align::Default, "MainMenu", "OptionsMenu");

	MyGUI::LayoutManager::getInstancePtr()->loadLayout(
		"$GAME_DATA/Gui/Layouts/Common/MenuBackButton.layout", "", self->m_pMainPanel);

	if (self->is_server)
	{
		MyGUI::LayoutManager::getInstancePtr()->loadLayout(
			"$GAME_DATA/Gui/Layouts/Options/Options_InGameMenu.layout",
			"",
			self->m_pMainPanel);
	}
	else
	{
		MyGUI::LayoutManager::getInstancePtr()->loadLayout(
			"$GAME_DATA/Gui/Layouts/Options/Options_MainMenu.layout",
			"",
			self->m_pMainPanel);
	}

	//Add custom tabs here
	{
		MyGUI::Widget* v_gfx_widget = self->m_pMainPanel->findWidget("Graphics");
		MyGUI::Widget* v_display_widget = self->m_pMainPanel->findWidget("Display");

		const MyGUI::IntCoord v_tab_data = v_display_widget->getCoord();
		const int v_distance = v_gfx_widget->getCoord().left - v_tab_data.right();

		const MyGUI::IntCoord v_new_tab_pos(
			v_gfx_widget->getRight() + v_distance,
			v_tab_data.top,
			v_tab_data.width,
			v_tab_data.height);

		MyGUI::Button* v_voice_chat_tab = v_gfx_widget->getParent()->createWidget<MyGUI::Button>(
			"InventoryTab", v_new_tab_pos, MyGUI::Align::Default, "ProximityVoiceChat");

		v_voice_chat_tab->setFontName("SM_Tab");
		v_voice_chat_tab->setCaption("VOICE CHAT");
		v_voice_chat_tab->setTextAlign(MyGUI::Align::Center);
	}

	MyGUI::Widget* v_back_widget = self->m_pMainPanel->findWidget("Back");
	v_back_widget->eventMouseButtonClick += MyGUI::newDelegate(
		(CustomOptionsMenu*)self, &CustomOptionsMenu::backPanelMouseClick);

	self->compound_button = std::make_shared<CompoundButton>(v_back_widget);

	std::vector<MyGUI::Button*> v_tabButtons;
	if (self->is_server)
		v_tabButtons.push_back(self->m_pMainPanel->findWidget("Gameplay")->castType<MyGUI::Button>());

	v_tabButtons.push_back(self->m_pMainPanel->findWidget("Controls")->castType<MyGUI::Button>());
	v_tabButtons.push_back(self->m_pMainPanel->findWidget("Audio")->castType<MyGUI::Button>());
	v_tabButtons.push_back(self->m_pMainPanel->findWidget("Display")->castType<MyGUI::Button>());
	v_tabButtons.push_back(self->m_pMainPanel->findWidget("Graphics")->castType<MyGUI::Button>());

	//Custom tab
	v_tabButtons.push_back(self->m_pMainPanel->findWidget("ProximityVoiceChat")->castType<MyGUI::Button>());

	for (auto& v_cur_tab : self->m_mapSubMenus)
	{
		if (v_cur_tab.second != self->m_currentTab)
			continue;

		MyGUI::Button* v_selectedTab = self->m_pMainPanel->findWidget(
			v_cur_tab.first)->castType<MyGUI::Button>();
		v_selectedTab->setStateSelected(true);
	}

	//Adjust the tab sizes
	int v_tab_offset = 0;
	for (MyGUI::Button* v_cur_tab : v_tabButtons)
	{
		if (!v_cur_tab) continue;

		const int v_cur_tab_width = v_cur_tab->getTextSize().width;
		const MyGUI::IntCoord& v_coord = v_cur_tab->getCoord();

		v_cur_tab->setCoord(
			v_tab_offset + v_coord.left,
			v_coord.top,
			v_coord.width + v_cur_tab_width,
			v_coord.height);

		v_tab_offset += v_cur_tab_width;
	}

	self->radio_btn_set = std::make_shared<RadioButtonSet>(v_tabButtons);

	//Initialize all the tabs
	MyGUI::Widget* v_optHostPanel = self->m_pMainPanel->findWidget("OptionsHostPanel");
	for (auto& v_cur_sub_menu : self->m_mapSubMenus)
		v_cur_sub_menu.second->initialize(v_optHostPanel);

	//Attach the tab switch callback to all the tabs
	for (MyGUI::Widget* v_cur_tab_widget : v_tabButtons)
		v_cur_tab_widget->eventMouseButtonClick += MyGUI::newDelegate(
			(CustomOptionsMenu*)self, &CustomOptionsMenu::switchTabCallback);

	self->m_pMainPanel->findWidget("Default")->eventMouseButtonClick += MyGUI::newDelegate(
		(CustomOptionsMenu*)self, &CustomOptionsMenu::defaultButtonClick);

	self->m_pMainPanel->setVisible(self->m_bSomeFlag);
	if (self->m_bSomeFlag)
		self->m_currentTab->openMenu();
}

void CustomOptionsMenu::backPanelMouseClick(MyGUI::Widget* widget)
{
	this->close();
	m_pMenuRootGui->open();
}

void CustomOptionsMenu::defaultButtonClick(MyGUI::Widget* widget)
{
	m_currentTab->restoreDefaults();
}

void CustomOptionsMenu::switchTabCallback(MyGUI::Widget* widget)
{
	auto v_iter = m_mapSubMenus.find(widget->getName());
	if (v_iter == m_mapSubMenus.end())
		return;

	if (v_iter->second != m_currentTab)
	{
		if (m_currentTab)
			m_currentTab->closeMenu();

		v_iter->second->openMenu();
		m_currentTab = v_iter->second;
	}
}