#pragma once

#include "SmSdk/AreaTriggerManager.hpp"

#include <DirectXMath.h>

#include <unordered_map>
#include <memory>

SMSDK_BEGIN_NAMESPACE

struct Portal : public NetObj
{
	/* 0x0028 */ SDK_MEM_PRI char pad_0x28[0x8];
	/* 0x0030 */ SDK_MEM_PUB DirectX::XMFLOAT3 m_position;
	/* 0x003C */ SDK_MEM_PRI char pad_0x3C[0x4];
	/* 0x0040 */ SDK_MEM_PUB AreaTrigger* m_pAreaTriggerA;
	/* 0x0048 */ SDK_MEM_PUB AreaTrigger* m_pAreaTriggerB;
}; // Size: 0x50

SMSDK_CHECK_MEMBER_OFFSET(Portal, m_position, 0x30);
SMSDK_CHECK_MEMBER_OFFSET(Portal, m_pAreaTriggerA, 0x40);
SMSDK_CHECK_MEMBER_OFFSET(Portal, m_pAreaTriggerB, 0x48);
SMSDK_CHECK_STRUCT_SIZE(Portal, 0x50);

//
// PORTAL MANAGER
//

struct PortalManager
{
	SDK_PUB SMSDK_API static PortalManager* GetInstance();

	/* 0x0000 */ SDK_MEM_PUB std::unordered_map<int, std::shared_ptr<Portal>> m_mapPortals;
	/* 0x0040 */ SDK_MEM_PRI char pad_0x40[0x58];
}; // Size: 0x98

SMSDK_CHECK_MEMBER_OFFSET(PortalManager, m_mapPortals, 0x0);
SMSDK_CHECK_STRUCT_SIZE(PortalManager, 0x98);

SMSDK_END_NAMESPACE