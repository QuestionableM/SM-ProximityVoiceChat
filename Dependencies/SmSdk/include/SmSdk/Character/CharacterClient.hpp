#pragma once

#include "SmSdk/config.hpp"

#include <DirectXMath.h>
#include <memory>

SMSDK_BEGIN_NAMESPACE

class CharacterGraphics
{
    SDK_PUB SMSDK_API std::shared_ptr<class GuiInterface> getNameTagGui();

	/* 0x0000 */ SDK_MEM_PUB std::shared_ptr<class Character> m_pCharacter;
	/* 0x0010 */ SDK_MEM_PUB std::shared_ptr<class AnimatedCharacter> m_pAnimatedCharacter;
	/* 0x0020 */ SDK_MEM_PUB std::uint32_t m_materialId;
	/* 0x0024 */ SDK_MEM_PUB DirectX::XMFLOAT3 m_upDirection;
	/* 0x0030 */ SDK_MEM_PUB std::shared_ptr<class GuiInterface> m_pNameTagGui;
	/* 0x0040 */ SDK_MEM_PRI char pad_0x40[0x4];
	/* 0x0044 */ SDK_MEM_PUB std::uint32_t m_nameTagUpdateCounter;
}; // Size: 0x48

SMSDK_CHECK_MEMBER_OFFSET(CharacterGraphics, m_pCharacter, 0x0);
SMSDK_CHECK_MEMBER_OFFSET(CharacterGraphics, m_pAnimatedCharacter, 0x10);
SMSDK_CHECK_MEMBER_OFFSET(CharacterGraphics, m_materialId, 0x20);
SMSDK_CHECK_MEMBER_OFFSET(CharacterGraphics, m_upDirection, 0x24);
SMSDK_CHECK_MEMBER_OFFSET(CharacterGraphics, m_pNameTagGui, 0x30);
SMSDK_CHECK_MEMBER_OFFSET(CharacterGraphics, m_nameTagUpdateCounter, 0x44);
SMSDK_CHECK_STRUCT_SIZE(CharacterGraphics, 0x48);

//
// CHARACTER CLIENT DATA
//

class CharacterClientData
{
	/* 0x0000 */ SDK_MEM_PUB std::shared_ptr<class AnimatedCharacter> m_pAnimatedCharacter;
	/* 0x0010 */ SDK_MEM_PUB std::shared_ptr<CharacterGraphics> m_pCharacterGfx;
}; // Size: 0x20

SMSDK_CHECK_MEMBER_OFFSET(CharacterClientData, m_pAnimatedCharacter, 0x0);
SMSDK_CHECK_MEMBER_OFFSET(CharacterClientData, m_pCharacterGfx, 0x10);
SMSDK_CHECK_STRUCT_SIZE(CharacterClientData, 0x20);

SMSDK_END_NAMESPACE