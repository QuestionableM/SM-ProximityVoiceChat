#pragma once

#include <SmSdk/Gui/OptionsItemSlider.hpp>

class PlayerVoiceSlider : public SM::OptionsItemSlider
{
public:
	PlayerVoiceSlider(
		MyGUI::Widget* parent,
		const std::string& playerName,
		const std::uint32_t playerId);

	void sliderChangePosition(MyGUI::ScrollBar* caller, const std::size_t newValue);
	void update() override;

private:
	std::uint32_t m_playerId;
};