#pragma once

#include "OptionsItemBase.hpp"

#include "SmSdk/Util/Memory.hpp"
#include "SmSdk/offsets.hpp"

#include <functional>
#include <string>

class OptionsItemSlider : public OptionsItemBase
{
public:
	virtual ~OptionsItemSlider() = default;
	OptionsItemSlider(
		MyGUI::Widget* widget,
		const std::string& caption,
		float min_value,
		float max_value,
		std::size_t scroll_range);

	void initializeSlider(MyGUI::Widget* parent, const std::string& caption);
	void updateValueText();
	float getFraction();
	void update() override {}

public:
	MyGUI::ScrollBar* m_pSlider;
	MyGUI::TextBox* m_pValueTextBox;
	std::size_t m_uSteps;
	float m_fMinValue;
	float m_fMaxValue;
};