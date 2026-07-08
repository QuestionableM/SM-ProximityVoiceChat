#include "PlayerVoiceSlider.hpp"

#include "PlayerVoiceManager.hpp"
#include "Utils/Console.hpp"

PlayerVoiceSlider::PlayerVoiceSlider(
	MyGUI::Widget* parent,
	const std::string_view& playerName,
	const std::uint32_t playerId
)
	: OptionsItemSlider(parent, playerName, 0.0f, 4.0f, 400)
	, m_playerId(playerId)
{
	// Pull the current volume and update the value
	this->update();

	m_pSlider->eventScrollChangePosition += MyGUI::newDelegate(
		this, &PlayerVoiceSlider::sliderChangePosition);
}

void PlayerVoiceSlider::sliderChangePosition(MyGUI::ScrollBar* caller, const std::size_t newValue)
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