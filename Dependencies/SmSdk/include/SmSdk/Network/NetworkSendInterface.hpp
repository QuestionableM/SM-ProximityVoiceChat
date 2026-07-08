#pragma once

#include "SmSdk/steamapi_include.hpp"
#include "SmSdk/config.hpp"

#include <unordered_map>

SMSDK_BEGIN_NAMESPACE

struct NetworkSendInterface
{
	/* 0x0000 */ SDK_PRI virtual void func1() {}

	/* 0x0008 */ SDK_MEM_PUB std::uint64_t m_uSentCompressedBytes;
	/* 0x0010 */ SDK_MEM_PUB std::uint64_t m_uSentRawBytes;
	/* 0x0018 */ SDK_MEM_PUB std::uint64_t m_uTick1;
	/* 0x0020 */ SDK_MEM_PUB std::uint64_t m_uTick2;
}; // Size: 0x28

SMSDK_CHECK_MEMBER_OFFSET(NetworkSendInterface, m_uSentCompressedBytes, 0x8);
SMSDK_CHECK_MEMBER_OFFSET(NetworkSendInterface, m_uSentRawBytes, 0x10);
SMSDK_CHECK_MEMBER_OFFSET(NetworkSendInterface, m_uTick1, 0x18);
SMSDK_CHECK_MEMBER_OFFSET(NetworkSendInterface, m_uTick2, 0x20);

SMSDK_CHECK_STRUCT_SIZE(NetworkSendInterface, 0x28);

//
// STEAM NETWORK SEND
//

struct SteamNetworkSend : public NetworkSendInterface
{
	SDK_PUB SMSDK_API std::vector<std::pair<std::uint64_t, HSteamNetConnection>> getAllConnections() const;
	SDK_PUB SMSDK_API HSteamNetConnection getConnectionFromSteamId(const std::uint64_t uSteamId) const;

	/* 0x0028 */ SDK_MEM_PUB std::unordered_map<std::uint64_t, HSteamNetConnection> m_mapSteamIdToConnection;
	/* 0x0068 */ SDK_MEM_PRI char pad_0x68[0xC0];
}; // Size: 0x128

SMSDK_CHECK_STRUCT_SIZE(SteamNetworkSend, 0x128);

SMSDK_END_NAMESPACE