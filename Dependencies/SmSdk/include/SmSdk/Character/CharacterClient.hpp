#pragma once

#include "SmSdk/config.hpp"

#include <DirectXMath.h>
#include <memory>

SMSDK_BEGIN_NAMESPACE

class CharacterGraphics
{
    SDK_PUB SMSDK_API std::shared_ptr<class GuiInterface> getNameTagGui();

	/* 0x0000 */ SDK_PUB std::shared_ptr<class Character> m_pCharacter;
	/* 0x0010 */ SDK_PUB std::shared_ptr<class AnimatedCharacter> m_pAnimatedCharacter;
	/* 0x0020 */ SDK_PUB std::uint32_t m_materialId;
	/* 0x0024 */ SDK_PUB DirectX::XMFLOAT3 m_upDirection;
	/* 0x0030 */ SDK_PUB std::shared_ptr<class GuiInterface> m_pNameTagGui;
	/* 0x0040 */ SDK_PRI char pad_0x40[0x4];
	/* 0x0044 */ SDK_PUB std::uint32_t m_nameTagUpdateCounter;
}; // Size: 0x48

static_assert(offsetof(CharacterGraphics, CharacterGraphics::m_pCharacter) == 0x0, "CharacterGraphics::m_pCharacter: Incorrect offset");
static_assert(offsetof(CharacterGraphics, CharacterGraphics::m_pAnimatedCharacter) == 0x10, "CharacterGraphics::m_pAnimatedCharacter: Incorrect offset");
static_assert(offsetof(CharacterGraphics, CharacterGraphics::m_materialId) == 0x20, "CharacterGraphics::m_materialId: Incorrect offset");
static_assert(offsetof(CharacterGraphics, CharacterGraphics::m_upDirection) == 0x24, "CharacterGraphics::m_upDirection: Incorrect offset");
static_assert(offsetof(CharacterGraphics, CharacterGraphics::m_pNameTagGui) == 0x30, "CharacterGraphics::m_pNameTagGui: Incorrect offset");
static_assert(offsetof(CharacterGraphics, CharacterGraphics::m_nameTagUpdateCounter) == 0x44, "CharacterGraphics::m_nameTagUpdateCounter: Incorrect offset");

static_assert(sizeof(CharacterGraphics) == 0x48, "CharacterGraphics: Incorrect Size");

class CharacterClientData
{
	/* 0x0000 */ SDK_PUB std::shared_ptr<class AnimatedCharacter> m_pAnimatedCharacter;
	/* 0x0010 */ SDK_PUB std::shared_ptr<CharacterGraphics> m_pCharacterGfx;
}; // Size: 0x20

static_assert(offsetof(CharacterClientData, CharacterClientData::m_pAnimatedCharacter) == 0x0, "CharacterClientData::m_pAnimatedCharacter: Incorrect offset");
static_assert(offsetof(CharacterClientData, CharacterClientData::m_pCharacterGfx) == 0x10, "CharacterClientData::m_pCharacterGfx: Incorrect offset");

static_assert(sizeof(CharacterClientData) == 0x20, "CharacterClientData: Incorrect Size");

SMSDK_END_NAMESPACE