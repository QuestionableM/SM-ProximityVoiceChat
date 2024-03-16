#include "VoiceChatSettingsTab.hpp"

#include <SmSdk/Gui/OptionsItemSlider.hpp>
#include <SmSdk/PlayerManager.hpp>

#include "PlayerVoiceManager.hpp"

#include "Utils/Console.hpp"

template<typename ...ArgList>
void call_vftable_func(std::size_t func_id, const ArgList& ...args)
{
	using fFuncType = void(*)(ArgList...);

	void** v_vftable = Memory::Read<void**>(SM_VTBL_OPTIONS_SUB_MENU_BASE_OFFSET);
	reinterpret_cast<fFuncType>(v_vftable[func_id])(args...);
}

VoiceChatSettingsTab::VoiceChatSettingsTab()
{
	void* v_old_vftable = *reinterpret_cast<void**>(this);
	OptionsSubMenuBase::GameConstructor(this);
	*reinterpret_cast<void**>(this) = v_old_vftable;
}

void VoiceChatSettingsTab::initialize(MyGUI::Widget* parent)
{
	call_vftable_func(1, this, parent);

	AttachDebugConsole();
	DebugOutL(__FUNCTION__);
}

void VoiceChatSettingsTab::cleanSomething()
{
	call_vftable_func(2, this);

	AttachDebugConsole();
	DebugOutL(__FUNCTION__);
}

void VoiceChatSettingsTab::openMenu()
{
	call_vftable_func(3, this);

	for (const auto& v_cur_voice : PlayerVoiceManager::sm_playerVoices)
	{
		Player* v_pPlayer = PlayerManager::GetPlayer(v_cur_voice.first);
		if (!v_pPlayer) continue;

		MyGUI::Widget* v_new_widget = this->options1.createNewOption();
		OptionsItemSlider* v_new_slider = new OptionsItemSlider(
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
	}

	AttachDebugConsole();
	DebugOutL(__FUNCTION__);
}

void VoiceChatSettingsTab::closeMenu()
{
	call_vftable_func(4, this);

	AttachDebugConsole();
	DebugOutL(__FUNCTION__);
}

void VoiceChatSettingsTab::onUpdate()
{
	call_vftable_func(5, this);
	
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
	call_vftable_func(9, this);

	AttachDebugConsole();
	DebugOutL(__FUNCTION__);
}