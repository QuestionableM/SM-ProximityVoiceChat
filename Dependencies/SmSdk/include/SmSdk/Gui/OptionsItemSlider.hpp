#pragma once

#include "SmSdk/Gui/OptionsItemBase.hpp"

#include "SmSdk/Util/Memory.hpp"
#include "SmSdk/offsets.hpp"

#include <functional>
#include <string>

SMSDK_BEGIN_NAMESPACE

class OptionsItemSlider : public OptionsItemBase
{
#if defined(SMSDK_ENABLE_MYGUI) || defined(SMSDK_BUILD_DLL) || defined(SMSDK_IMPORT_DLL)
	SDK_PUB SMSDK_API OptionsItemSlider(
		MyGUI::Widget* pWidget,
		const std::string_view& caption,
		const float fMinValue,
		const float fMaxValue,
		const std::size_t iScrollRange);
	
	SDK_PUB SMSDK_API void initializeSlider(MyGUI::Widget* pParent, const std::string_view& caption);
	SDK_PUB SMSDK_API void updateValueText();

	SDK_PUB SMSDK_API float getFraction() const;
#endif

	SDK_PUB SMSDK_API virtual ~OptionsItemSlider() = default;
	SDK_PUB SMSDK_API void update() override {}
	
	SDK_PUB MyGUI::ScrollBar* m_pSlider;
	SDK_PUB MyGUI::TextBox* m_pValueTextBox;
	SDK_PUB size_t m_uSteps;
	SDK_PUB float m_fMinValue;
	SDK_PUB float m_fMaxValue;
};

static_assert(offsetof(OptionsItemSlider, OptionsItemSlider::m_pSlider) == 0x10, "OptionsItemSlider::m_pSlider: Incorrect offset");

SMSDK_END_NAMESPACE