#include "VoiceChatSettingsTab.hpp"

#include <SmSdk/PlayerManager.hpp>

#include "VoiceSettingsStorage.hpp"
#include "PlayerVoiceManager.hpp"
#include "PlayerVoiceSlider.hpp"
#include "Utils/Console.hpp"

VoiceChatSettingsTab::VoiceChatSettingsTab()
	: OptionsSubMenuBase()
	, m_registeredVoices()
	, m_pEmptyListText(nullptr)
{}

void VoiceChatSettingsTab::initialize(MyGUI::Widget* parent)
{
	OptionsSubMenuBase::initialize(parent);

	m_pEmptyListText = this->getSubMenuWidget()->createWidgetReal<MyGUI::TextBox>(
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

	// Find new voices
	for (const auto& v_curVoice : PlayerVoiceManager::sm_playerVoices)
	{
		if (m_registeredVoices.contains(v_curVoice.first))
			continue;

		AttachDebugConsole();
		DebugOutL(__FUNCTION__, " -> Registered a new voice: ", v_curVoice.first);

		m_registeredVoices.emplace(v_curVoice.first);
		v_result = true;
	}

	// Drop dead voices
	for (auto v_iter = m_registeredVoices.begin(); v_iter != m_registeredVoices.end();)
	{
		if (PlayerVoiceManager::sm_playerVoices.contains(*v_iter))
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

	this->clear(false);

	std::size_t v_voiceCount = 0;
	for (const auto& v_cur_voice : PlayerVoiceManager::sm_playerVoices)
	{
		auto v_pVoiceOwner = SM::PlayerManager::GetPlayer(v_cur_voice.first);
		if (!v_pVoiceOwner) continue;

		SM::VerticalStackBox* v_pStackBox = ((v_voiceCount % 2) == 0)
			? this->getLeftStackBox() : this->getRightStackBox();

		MyGUI::Widget* v_pNewWidget = v_pStackBox->createNewOption();
		auto v_pNewSlider = std::make_shared<PlayerVoiceSlider>(
			v_pNewWidget, v_pVoiceOwner->getName(), v_pVoiceOwner->getId());

		this->addOptionItem(v_pNewSlider);
		v_voiceCount++;
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