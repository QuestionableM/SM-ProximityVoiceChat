#pragma once

#include "SteamNetworkServer.hpp"
#include "SmSdk/config.hpp"

SMSDK_BEGIN_NAMESPACE

struct ListenServer
{
	/* 0x0000 */ SDK_MEM_PUB SteamNetworkServer* m_pNetworkServer;
	/* 0x0008 */ SDK_MEM_PRI char pad_0x8[0x1B8];
}; // Size: 0x1C0

SMSDK_CHECK_STRUCT_SIZE(ListenServer, 0x1C0);

SMSDK_END_NAMESPACE