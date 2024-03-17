#include "VoiceChatSettingsTab.hpp"

#include <SmSdk/Gui/OptionsItemSlider.hpp>
#include <SmSdk/PlayerManager.hpp>

#include "PlayerVoiceManager.hpp"

#include "Utils/Console.hpp"

VoiceChatSettingsTab::VoiceChatSettingsTab()
	: OptionsSubMenuBase()
{
}

void VoiceChatSettingsTab::initialize(MyGUI::Widget* parent)
{
	OptionsSubMenuBase::initialize(parent);

	AttachDebugConsole();
	DebugOutL(__FUNCTION__);
}

void VoiceChatSettingsTab::openMenu()
{
	for (int a = 0; a < 100; a++)
	{
		VerticalStackBox& v_cur_stack_box = (a % 2) ? m_leftStackBox : m_rightStackBox;

		MyGUI::Widget* v_new_widget = v_cur_stack_box.createNewOption();
		auto v_new_slider = std::make_shared<OptionsItemSlider>(
			v_new_widget, std::to_string(a), "Test" + std::to_string(a), 0.0f, 1.0f, 500,
			[](std::size_t value) -> void {}
		);

		m_optionItems.push_back(std::move(v_new_slider));
	}

	for (const auto& v_cur_voice : PlayerVoiceManager::sm_playerVoices)
	{
		Player* v_pPlayer = PlayerManager::GetPlayer(v_cur_voice.first);
		if (!v_pPlayer) continue;

		MyGUI::Widget* v_new_widget = m_leftStackBox.createNewOption();
		auto v_new_slider = std::make_shared<OptionsItemSlider>(
			v_new_widget, v_pPlayer->name, "VolumeSlider", 0.0f, 1.0f, 500,
			[v_pl_id = v_cur_voice.first](std::size_t value) -> void {
				const float v_flt_val = *reinterpret_cast<float*>(&value);

				AttachDebugConsole();
				DebugOutL(__FUNCTION__, " -> ", v_flt_val);

				PlayerVoice* v_plVoice = PlayerVoiceManager::GetVoice(v_pl_id);
				if (!v_plVoice) return;

				v_plVoice->m_fVolume = v_flt_val * 50.0f;
			}
		);

		m_optionItems.push_back(std::move(v_new_slider));
	}

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

void VoiceChatSettingsTab::onUpdate()
{
	AttachDebugConsole();
	DebugOutL(__FUNCTION__);
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