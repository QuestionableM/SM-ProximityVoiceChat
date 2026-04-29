#pragma once

#include "SmSdk/boost_include.hpp"
#include "SmSdk/config.hpp"

#include "SmSdk/Character.hpp"

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

	SDK_PUB SMSDK_API Character* getCharacter(const std::uint32_t uCharId);
	SDK_PUB SMSDK_API std::span<std::shared_ptr<Character>> getAllCharacters();

	SDK_PUB SMSDK_API static Character* GetCharacter(const std::uint32_t uCharId);
	SDK_PUB SMSDK_API static std::span<std::shared_ptr<Character>> GetAllCharacters();

	/* 0x0008 */ SDK_PUB std::unordered_map<std::uint32_t, std::shared_ptr<Character>> m_mapCharacterState;
	/* 0x0048 */ SDK_PUB std::unordered_map<std::uint32_t, std::shared_ptr<struct Lift>> m_worldLiftMap;
	/* 0x0088 */ SDK_PRI std::int32_t m_iSomeId;
	/* 0x008C */ SDK_PUB std::uint32_t m_uTick;
	/* 0x0090 */ SDK_PUB std::map<boost::uuids::uuid, struct CharacterData> m_mapCharacterData;
	/* 0x00A0 */ SDK_PUB std::vector<std::shared_ptr<Character>> m_vecCharacters;
}; // Size: 0xB8

static_assert(sizeof(CharacterManager) == 0xB8, "CharacterManager: Incorrect Size");

SMSDK_END_NAMESPACE