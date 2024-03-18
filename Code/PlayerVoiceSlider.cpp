#include "PlayerVoiceSlider.hpp"

#include "PlayerVoiceManager.hpp"
#include "Utils/Console.hpp"

PlayerVoiceSlider::PlayerVoiceSlider(
	MyGUI::Widget* parent,
	const std::string& player_name,
	int player_id)
	: OptionsItemSlider(parent, player_name, 0.0f, 2.0f, 200),
	m_playerId(player_id)
{
	//Pull the current volume and update the value
	this->update();

	m_pSlider->eventScrollChangePosition += MyGUI::newDelegate(
		this, &PlayerVoiceSlider::sliderChangePosition);
}

void PlayerVoiceSlider::sliderChangePosition(MyGUI::ScrollBar* caller, std::size_t new_value)
{
	PlayerVoice* v_voice = PlayerVoiceManager::GetVoice(m_playerId);
	if (!v_voice) return;

	v_voice->setVolume(this->getFraction());
	this->updateValueText();
}

void PlayerVoiceSlider::update()
{
	PlayerVoice* v_cur_voice = PlayerVoiceManager::GetVoice(m_playerId);
	if (!v_cur_voice) return;

	m_pSlider->setScrollPosition(std::size_t(v_cur_voice->m_fVolume * 100.0f));
	this->updateValueText();
}