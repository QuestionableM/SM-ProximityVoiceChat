#include "VoiceChatSettingsTab.hpp"

#include <SmSdk/Gui/OptionsItemSlider.hpp>
#include <SmSdk/PlayerManager.hpp>

#include "VoiceSettingsStorage.hpp"
#include "PlayerVoiceManager.hpp"
#include "PlayerVoiceSlider.hpp"
#include "Utils/Console.hpp"

VoiceChatSettingsTab::VoiceChatSettingsTab()
	: OptionsSubMenuBase(),
	m_registeredVoices(),
	m_pEmptyListText(nullptr)
{
}

void VoiceChatSettingsTab::initialize(MyGUI::Widget* parent)
{
	OptionsSubMenuBase::initialize(parent);

	m_pEmptyListText = m_pSubMenuWidget->createWidgetReal<MyGUI::TextBox>(
		"TextBox", MyGUI::FloatCoord(0, 0, 1.0f, 1.0f), MyGUI::Align::Center);

	m_pEmptyListText->setFontName("SM_HeaderLarge_Wide");
	m_pEmptyListText->setCaption("NO PLAYERS");
	m_pEmptyListText->setTextAlign(MyGUI::Align::Center);
	m_pEmptyListText->setNeedMouseFocus(false);
	m_pEmptyListText->setNeedKeyFocus(false);
	m_pEmptyListText->setVisible(false);
		
	AttachDebugConsole();
	DebugOutL(__FUNCTION__);
}

void VoiceChatSettingsTab::openMenu()
{
	this->updateScrollArea();

	OptionsSubMenuBase::openMenu();

	AttachDebugConsole();
	DebugOutL(__FUNCTION__);
}

void VoiceChatSettingsTab::closeMenu()
{
	OptionsSubMenuBase::closeMenu();

	AttachDebugConsole();
	DebugOutL(__FUNCTION__);
}

bool VoiceChatSettingsTab::shouldUpdateVoices()
{
	bool v_result = false;

	//Find new voices
	for (const auto& v_cur_voice : PlayerVoiceManager::sm_playerVoices)
	{
		if (m_registeredVoices.find(v_cur_voice.first) != m_registeredVoices.end())
			continue;

		AttachDebugConsole();
		DebugOutL(__FUNCTION__, " -> Registered a new voice: ", v_cur_voice.first);

		m_registeredVoices.emplace(v_cur_voice.first);
		v_result = true;
	}

	//Drop dead voices
	for (auto v_iter = m_registeredVoices.begin(); v_iter != m_registeredVoices.end();)
	{
		if (PlayerVoiceManager::sm_playerVoices.find(*v_iter) != PlayerVoiceManager::sm_playerVoices.end())
		{
			v_iter++;
			continue;
		}

		AttachDebugConsole();
		DebugOutL(__FUNCTION__, " -> Removed a dead voice: ", *v_iter);

		v_iter = m_registeredVoices.erase(v_iter);
		v_result = true;
	}

	return v_result;
}

void VoiceChatSettingsTab::onUpdate()
{
	m_pEmptyListText->setVisible(PlayerVoiceManager::sm_playerVoices.empty());

	if (!this->shouldUpdateVoices())
		return;

	this->clearSilent();

	std::size_t v_voice_count = 0;
	for (const auto& v_cur_voice : PlayerVoiceManager::sm_playerVoices)
	{
		Player* v_voice_owner = PlayerManager::GetPlayer(v_cur_voice.first);
		if (!v_voice_owner) continue;

		VerticalStackBox& v_stack_box = ((v_voice_count % 2) == 0)
			? m_leftStackBox : m_rightStackBox;

		MyGUI::Widget* v_new_widget = v_stack_box.createNewOption();
		auto v_new_slider = std::make_shared<PlayerVoiceSlider>(
			v_new_widget, v_voice_owner->name, v_voice_owner->id);

		m_optionItems.push_back(std::move(v_new_slider));
		v_voice_count++;
	}

	this->updateScrollAreaAndScrollBar();
}

void VoiceChatSettingsTab::restoreDefaults()
{
	AttachDebugConsole();
	DebugOutL(__FUNCTION__);
}

void VoiceChatSettingsTab::someFunc4()
{
	AttachDebugConsole();
	DebugOutL(__FUNCTION__);
}