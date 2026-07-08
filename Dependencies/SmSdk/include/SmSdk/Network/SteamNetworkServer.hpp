#pragma once

#include "SmSdk/Network/NetworkServer.hpp"

SMSDK_BEGIN_NAMESPACE

struct SteamNetworkServer : public NetworkServer
{
	SDK_PUB SMSDK_API std::shared_ptr<SteamNetworkSend> getNetworkSend();

	/* 0x0030 */ SDK_MEM_PRI char pad_0x30[0xF8];
}; // Size: 0x128

SMSDK_CHECK_STRUCT_SIZE(SteamNetworkServer, 0x128);

SMSDK_END_NAMESPACE