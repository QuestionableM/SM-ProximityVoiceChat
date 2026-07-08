#pragma once

#include "SmSdk/Network/NetworkSendInterface.hpp"
#include "SmSdk/config.hpp"

#include <memory>

SMSDK_BEGIN_NAMESPACE

struct NetworkServer
{
	SDK_PRI virtual void func1() {}

	/* 0x0008 */ SDK_MEM_PUB std::shared_ptr<NetworkSendInterface> m_pNetworkSend;
	/* 0x0018 */ SDK_MEM_PUB std::shared_ptr<struct ClientCommunication> m_pClientCommunication;
	/* 0x0028 */ SDK_MEM_PRI char pad_0x28[0x8];
}; // Size: 0x30

SMSDK_CHECK_MEMBER_OFFSET(NetworkServer, m_pNetworkSend, 0x8);
SMSDK_CHECK_MEMBER_OFFSET(NetworkServer, m_pClientCommunication, 0x18);
SMSDK_CHECK_STRUCT_SIZE(NetworkServer, 0x30);

SMSDK_END_NAMESPACE