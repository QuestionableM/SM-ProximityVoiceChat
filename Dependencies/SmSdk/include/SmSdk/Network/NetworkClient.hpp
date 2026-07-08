#pragma once

#include "SmSdk/Network/NetworkSendInterface.hpp"
#include "SmSdk/steamapi_include.hpp"

#include <unordered_map>
#include <memory>
#include <string>

SMSDK_BEGIN_NAMESPACE

class NetworkClient
{
	/* 0x0000 */ SDK_MEM_PRI char pad_0x0[0x8];
	/* 0x0008 */ SDK_MEM_PUB std::shared_ptr<NetworkSendInterface> m_pNetworkSend;
	/* 0x0018 */ SDK_MEM_PUB std::int32_t m_iConnectionState;
	/* 0x001C */ SDK_MEM_PRI char pad_0x1C[0x2C];
	/* 0x0048 */ SDK_MEM_PRI std::string m_someString1;
	/* 0x0068 */ SDK_MEM_PRI char pad_0x68[0x80];
	/* 0x00E8 */ SDK_MEM_PUB std::shared_ptr<struct TickLag> m_pTickLag;
	/* 0x00F8 */ SDK_MEM_PRI char pad_0xF8[0x38];
}; // Size: 0x130

SMSDK_CHECK_STRUCT_SIZE(NetworkClient, 0x130);

SMSDK_END_NAMESPACE