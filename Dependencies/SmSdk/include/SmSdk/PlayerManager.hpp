#pragma once

#include "SmSdk/Player.hpp"

#include <unordered_map>
#include <vector>
#include <memory>

SMSDK_BEGIN_NAMESPACE

class PlayerManager
{
	SDK_PUB SMSDK_API static PlayerManager* GetInstance();

	SDK_PUB SMSDK_API std::shared_ptr<Player> getPlayer(const std::uint32_t playerId);
	SDK_PUB SMSDK_API std::shared_ptr<Player> getPlayerFromSteamId(const std::uint64_t steamId);
	SDK_PUB SMSDK_API std::vector<std::shared_ptr<Player>> getAllPlayers();

	SDK_PUB SMSDK_API static std::shared_ptr<Player> GetPlayer(const std::uint32_t playerId);
	SDK_PUB SMSDK_API static std::shared_ptr<Player> GetPlayerFromSteamId(const std::uint64_t steamId);
	SDK_PUB SMSDK_API static std::vector<std::shared_ptr<Player>> GetAllPlayers();

	/* 0x0000 */ SDK_MEM_PUB std::int32_t m_iTick;
	/* 0x0004 */ SDK_MEM_PRI char pad_0x4[0x4];
	/* 0x0008 */ SDK_MEM_PUB std::unordered_map<std::uint32_t, std::shared_ptr<Player>> m_mapIdToPlayers;
	/* 0x0048 */ SDK_MEM_PUB std::unordered_map<std::uint64_t, std::uint32_t> m_mapSteamIdToPlayer;
	/* 0x0088 */ SDK_MEM_PRI char pad_0x88[0xC0];
}; // Size: 0x148

SMSDK_CHECK_STRUCT_SIZE(PlayerManager, 0x148);

SMSDK_END_NAMESPACE