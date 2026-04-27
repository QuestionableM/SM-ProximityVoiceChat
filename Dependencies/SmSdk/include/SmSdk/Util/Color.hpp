#pragma once

#include "SmSdk/config.hpp"

#include <string>
#include <cmath>

SMSDK_BEGIN_NAMESPACE

union Color;

#pragma warning(push)
#pragma warning(disable : 4201)

union ColorBGRA
{
	ColorBGRA() = default;
	ColorBGRA(const Color color);

	std::uint32_t data;
	struct { std::uint8_t b, g, r, a; };
};

union Color
{
	Color() = default;
	SMSDK_API Color(const ColorBGRA col);
	SMSDK_API Color(const std::uint32_t col);
	SMSDK_API Color(const std::uint64_t col);
	SMSDK_API Color(const std::string& col);

	SMSDK_API float getFloat(const std::size_t iIdx) const;
	SMSDK_API void setFloat(const std::size_t iIdx, const float fVal);

	SMSDK_API std::string toHexStringRGB() const;
	SMSDK_API bool operator==(const Color other) const noexcept;

	static SMSDK_API void RGBtoHSV(const Color col, float& fH, float& fS, float& fV);
	static SMSDK_API std::uint32_t RatioToRGB(const double dRatio);

	std::uint32_t data;
	struct { std::uint8_t r, g, b, a; };
	std::uint8_t colArr[4];
};

#pragma warning(pop)

SMSDK_END_NAMESPACE