#pragma once

#include <SmSdk/Gui/OptionsItemSlider.hpp>

class PlayerVoiceSlider : public OptionsItemSlider
{
public:
	PlayerVoiceSlider(
		MyGUI::Widget* parent,
		const std::string& player_name,
		int player_id);

	void sliderChangePosition(MyGUI::ScrollBar* caller, std::size_t new_value);
	void update() override;

private:
	int m_playerId;
};