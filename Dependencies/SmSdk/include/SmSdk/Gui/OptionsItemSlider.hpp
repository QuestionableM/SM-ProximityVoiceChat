#pragma once

#include "OptionsItemBase.hpp"

#include "SmSdk/Util/Memory.hpp"
#include "SmSdk/offsets.hpp"

#include <functional>
#include <string>

class OptionsItemSlider : public OptionsItemBase
{
public:
	OptionsItemSlider(MyGUI::Widget* widget,
		const std::string& caption,
		const std::string& name,
		float min_value,
		float max_value,
		std::size_t scroll_range,
		const std::function<void(std::size_t)>& callback)
	{
		using OptionsItemSliderConstructor = void (*)(
			OptionsItemSlider* self,
			MyGUI::Widget* widget,
			const std::string& caption,
			const std::string& name,
			float min_value,
			float max_value,
			size_t scroll_range,
			const std::function<void(std::size_t)>& callback
		);

		OptionsItemSliderConstructor v_constructor = Memory::Read<OptionsItemSliderConstructor>(
			SM_CONSTRUCTOR_OPTIONS_ITEM_SLIDER_OFFSET);
		v_constructor(this, widget, caption, name, min_value, max_value, scroll_range, callback);
	}

	virtual ~OptionsItemSlider() = default;
	void update() override { /* implemented by the game */ }

private:
	/* 0x0010 */ char pad_0x10[0x10];
public:
	/* 0x0020 */ std::string name;
private:
	/* 0x0040 */ char pad_0x40[0x4];
public:
	/* 0x0044 */ float min_value;
	/* 0x0048 */ float max_value;
private:
	/* 0x004C */ char pad_0x4C[0x4];
public:
	/* 0x0050 */ __int64 m_uSteps;
private:
	/* 0x0058 */ char pad_0x58[0x98];
}; // Size: 0xF0

static_assert(offsetof(OptionsItemSlider, OptionsItemSlider::name) == 0x20, "OptionsItemSlider::name: Incorrect offset");
static_assert(offsetof(OptionsItemSlider, OptionsItemSlider::min_value) == 0x44, "OptionsItemSlider::min_value: Incorrect offset");
static_assert(offsetof(OptionsItemSlider, OptionsItemSlider::max_value) == 0x48, "OptionsItemSlider::max_value: Incorrect offset");
static_assert(offsetof(OptionsItemSlider, OptionsItemSlider::m_uSteps) == 0x50, "OptionsItemSlider::m_uSteps: Incorrect offset");

static_assert(sizeof(OptionsItemSlider) == 0xF0, "OptionsItemSlider: Incorrect Size");