#pragma once

#include "SmSdk/Network/NetworkSendInterface.hpp"
#include "SmSdk/config.hpp"

#include <memory>

SMSDK_BEGIN_NAMESPACE

struct NetworkServer
{
	SDK_PRI virtual void func1() {}

	/* 0x0008 */ SDK_PUB std::shared_ptr<NetworkSendInterface> m_pNetworkSend;
	/* 0x0018 */ SDK_PUB std::shared_ptr<struct ClientCommunication> m_pClientCommunication;
	/* 0x0028 */ SDK_PRI char pad_0x28[0x8];
}; // Size: 0x30

static_assert(offsetof(NetworkServer, NetworkServer::m_pNetworkSend) == 0x8, "NetworkServer::m_pNetworkSend: Incorrect offset");
static_assert(offsetof(NetworkServer, NetworkServer::m_pClientCommunication) == 0x18, "NetworkServer::m_pClientCommunication: Incorrect offset");

static_assert(sizeof(NetworkServer) == 0x30, "NetworkServer: Incorrect Size");

SMSDK_END_NAMESPACE