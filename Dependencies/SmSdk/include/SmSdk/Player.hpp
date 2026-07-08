#pragma once

#include <memory>
#include <string>

#include "SmSdk/boost_include.hpp"
#include <DirectXMath.h>

SMSDK_BEGIN_NAMESPACE

struct PlayerGarments
{
	/* 0x0000 */ SDK_MEM_PUB bool m_bIsFemale;
	/* 0x0001 */ SDK_MEM_PUB boost::uuids::uuid m_headUuid;
	/* 0x0011 */ SDK_MEM_PUB boost::uuids::uuid m_hairUuid;
	/* 0x0021 */ SDK_MEM_PUB boost::uuids::uuid m_facialHairUuid;
	/* 0x0031 */ SDK_MEM_PUB boost::uuids::uuid m_torsoUuid;
	/* 0x0041 */ SDK_MEM_PUB boost::uuids::uuid m_glovesUuid;
	/* 0x0051 */ SDK_MEM_PUB boost::uuids::uuid m_shoesUuid;
	/* 0x0061 */ SDK_MEM_PUB boost::uuids::uuid m_legsUuid;
	/* 0x0071 */ SDK_MEM_PUB boost::uuids::uuid m_hatUuid;
	/* 0x0081 */ SDK_MEM_PUB boost::uuids::uuid m_backpackUuid;
	/* 0x0091 */ SDK_MEM_PUB char pad_0x91[0x3];
	/* 0x0094 */ SDK_MEM_PUB std::int32_t m_headColor;
	/* 0x0098 */ SDK_MEM_PUB std::int32_t m_hairColor;
	/* 0x009C */ SDK_MEM_PUB std::int32_t m_facialHairColor;
	/* 0x00A0 */ SDK_MEM_PUB std::int32_t m_torsoColor;
	/* 0x00A4 */ SDK_MEM_PUB std::int32_t m_glovesColor;
	/* 0x00A8 */ SDK_MEM_PUB std::int32_t m_shoesColor;
	/* 0x00AC */ SDK_MEM_PUB std::int32_t m_legsColor;
	/* 0x00B0 */ SDK_MEM_PUB std::int32_t m_hatColor;
	/* 0x00B4 */ SDK_MEM_PUB std::int32_t m_backpackColor;
}; // Size: 0xB8

SMSDK_CHECK_STRUCT_SIZE(PlayerGarments, 0xB8);

struct PlayerScriptData
{
	/* 0x0000 */ SDK_MEM_PUB bool m_bHasServerOnRefresh;
	/* 0x0001 */ SDK_MEM_PUB bool m_bHasServerOnProjectile;
	/* 0x0002 */ SDK_MEM_PUB bool m_bHasServerOnExplosion;
	/* 0x0003 */ SDK_MEM_PUB bool m_bHasServerOnMelee;
	/* 0x0004 */ SDK_MEM_PUB bool m_bHasServerOnCollision;
	/* 0x0005 */ SDK_MEM_PUB bool m_bHasServerOnCollisionCrush;
	/* 0x0006 */ SDK_MEM_PUB bool m_bHasServerOnShapeRemoved;
	/* 0x0007 */ SDK_MEM_PUB bool m_bHasServerOnInventoryChanges;
}; // Size: 0x8

SMSDK_CHECK_STRUCT_SIZE(PlayerScriptData, 0x8);

class Character;

class Player : public std::enable_shared_from_this<Player>
{
	SDK_PUB SMSDK_API std::uint64_t getSteamId() const;
	SDK_PUB SMSDK_API std::uint32_t getId() const;
	SDK_PUB SMSDK_API std::uint32_t getCharacterId() const;
	SDK_PUB SMSDK_API std::uint16_t getWorldId() const;
	SDK_PUB SMSDK_API std::string_view getName() const;

	SDK_PUB SMSDK_API std::shared_ptr<Character> getCharacter() const;
	SDK_PUB SMSDK_API bool characterExists() const;

	/* 0x0010 */ SDK_MEM_PUB std::uint32_t m_uId;
	/* 0x0014 */ SDK_MEM_PUB std::uint32_t m_uCharacterId;
	/* 0x0018 */ SDK_MEM_PUB std::uint16_t m_uWorldId;
	/* 0x001A */ SDK_MEM_PRI char pad_0x1A[0x2];
	/* 0x001C */ SDK_MEM_PUB DirectX::XMFLOAT3 m_characterPosition;
	/* 0x0028 */ SDK_MEM_PUB DirectX::XMFLOAT3 m_characterVelocity;
	/* 0x0034 */ SDK_MEM_PUB float m_fCharacterYaw;
	/* 0x0038 */ SDK_MEM_PUB float m_fCharacterPitch;
	/* 0x003C */ SDK_MEM_PRI char pad_0x3C[0x4];
	/* 0x0040 */ SDK_MEM_PUB std::uint64_t m_uSteamId;
	/* 0x0048 */ SDK_MEM_PUB std::string m_name;
	/* 0x0068 */ SDK_MEM_PUB std::uint32_t m_uDrawDistanceSetting;
	/* 0x006C */ SDK_MEM_PUB PlayerGarments m_garments;
	/* 0x0124 */ SDK_MEM_PUB std::uint32_t m_uGarmentChangeCounter;
	/* 0x0128 */ SDK_MEM_PRI char pad_0x128[0x10];
	/* 0x0138 */ SDK_MEM_PUB std::int32_t m_scriptRef;
	/* 0x013C */ SDK_MEM_PUB PlayerScriptData m_scriptData;
	/* 0x0144 */ SDK_MEM_PRI char pad_0x144[0xC];
}; // Size: 0x150

SMSDK_CHECK_MEMBER_OFFSET(Player, m_uId, 0x10);
SMSDK_CHECK_MEMBER_OFFSET(Player, m_uCharacterId, 0x14);
SMSDK_CHECK_MEMBER_OFFSET(Player, m_uWorldId, 0x18);
SMSDK_CHECK_MEMBER_OFFSET(Player, m_characterPosition, 0x1C);
SMSDK_CHECK_MEMBER_OFFSET(Player, m_characterVelocity, 0x28);
SMSDK_CHECK_MEMBER_OFFSET(Player, m_fCharacterYaw, 0x34);
SMSDK_CHECK_MEMBER_OFFSET(Player, m_fCharacterPitch, 0x38);
SMSDK_CHECK_MEMBER_OFFSET(Player, m_uSteamId, 0x40);
SMSDK_CHECK_MEMBER_OFFSET(Player, m_name, 0x48);
SMSDK_CHECK_MEMBER_OFFSET(Player, m_uDrawDistanceSetting, 0x68);
SMSDK_CHECK_MEMBER_OFFSET(Player, m_garments, 0x6C);
SMSDK_CHECK_MEMBER_OFFSET(Player, m_uGarmentChangeCounter, 0x124);
SMSDK_CHECK_MEMBER_OFFSET(Player, m_scriptRef, 0x138);
SMSDK_CHECK_MEMBER_OFFSET(Player, m_scriptData, 0x13C);
SMSDK_CHECK_STRUCT_SIZE(Player, 0x150);

SMSDK_END_NAMESPACE