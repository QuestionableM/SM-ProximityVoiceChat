#pragma once

#include "SmSdk/boost_include.hpp"
#include "SmSdk/config.hpp"

#include "SmSdk/Character/CharacterClient.hpp"
#include "SmSdk/Character/Character.hpp"

#include <unordered_map>
#include <vector>
#include <memory>
#include <span>
#include <map>

SMSDK_BEGIN_NAMESPACE

class CharacterManager
{
	REMOVE_COPY_CONSTRUCTORS(CharacterManager);
	SDK_PUB virtual ~CharacterManager() = default;

	SDK_PUB SMSDK_API static CharacterManager* GetInstance();

	SDK_PUB SMSDK_API std::shared_ptr<Character> getCharacter(const std::uint32_t uCharId);
	SDK_PUB SMSDK_API std::span<std::shared_ptr<Character>> getAllCharacters();

	SDK_PUB SMSDK_API static std::shared_ptr<Character> GetCharacter(const std::uint32_t uCharId);
	SDK_PUB SMSDK_API static std::span<std::shared_ptr<Character>> GetAllCharacters();

	/* 0x0008 */ SDK_MEM_PUB std::unordered_map<std::uint32_t, std::shared_ptr<Character>> m_mapCharacterState;
	/* 0x0048 */ SDK_MEM_PUB std::unordered_map<std::uint32_t, std::shared_ptr<struct Lift>> m_worldLiftMap;
	/* 0x0088 */ SDK_MEM_PRI std::int32_t m_iSomeId;
	/* 0x008C */ SDK_MEM_PUB std::uint32_t m_uTick;
	/* 0x0090 */ SDK_MEM_PUB std::map<boost::uuids::uuid, struct CharacterData> m_mapCharacterData;
	/* 0x00A0 */ SDK_MEM_PUB std::vector<std::shared_ptr<Character>> m_vecCharacters;
}; // Size: 0xB8

SMSDK_CHECK_MEMBER_OFFSET(CharacterManager, m_mapCharacterState, 0x8);
SMSDK_CHECK_MEMBER_OFFSET(CharacterManager, m_worldLiftMap, 0x48);
SMSDK_CHECK_MEMBER_OFFSET(CharacterManager, m_uTick, 0x8C);
SMSDK_CHECK_MEMBER_OFFSET(CharacterManager, m_mapCharacterData, 0x90);
SMSDK_CHECK_MEMBER_OFFSET(CharacterManager, m_vecCharacters, 0xA0);
SMSDK_CHECK_STRUCT_SIZE(CharacterManager, 0xB8);

//
// CHARACTER MANAGER CLIENT
//

class CharacterManagerClient : public CharacterManager
{
	REMOVE_COPY_CONSTRUCTORS(CharacterManagerClient);

	SDK_PUB SMSDK_API static CharacterManagerClient* GetInstance();

	SDK_PUB SMSDK_API std::shared_ptr<CharacterGraphics> getCharacterGraphics(const std::uint32_t uCharId);
	SDK_PUB SMSDK_API static std::shared_ptr<CharacterGraphics> GetCharacterGraphics(const std::uint32_t uCharId);

	/* 0x00B8 */ SDK_MEM_PUB std::uint16_t m_uWorldId;
	/* 0x00BA */ SDK_MEM_PRI char pad_0xBA[0x6];
	/* 0x00C0 */ SDK_MEM_PUB std::map<std::uint32_t, CharacterClientData> m_mapCharacterGraphics;
	/* 0x00D0 */ SDK_MEM_PUB std::map<std::uint32_t, std::shared_ptr<struct LiftGraphics>> m_mapLiftGraphics;
	/* 0x00E0 */ SDK_MEM_PRI char pad_0xE0[0x28];
}; // Size: 0x108

SMSDK_CHECK_MEMBER_OFFSET(CharacterManagerClient, m_uWorldId, 0xB8);
SMSDK_CHECK_MEMBER_OFFSET(CharacterManagerClient, m_mapCharacterGraphics, 0xC0);
SMSDK_CHECK_MEMBER_OFFSET(CharacterManagerClient, m_mapLiftGraphics, 0xD0);
SMSDK_CHECK_STRUCT_SIZE(CharacterManagerClient, 0x108);

SMSDK_END_NAMESPACE