#pragma once

#include "SmSdk/Physics/AreaTriggerProxy.hpp"
#include "SmSdk/bullet_include.hpp"
#include "SmSdk/Base/Task.hpp"

#include <DirectXMath.h>
#include <concrt.h>

#include <unordered_map>
#include <vector>

SMSDK_BEGIN_NAMESPACE

struct AreaTrigger
{
	/* 0x0000 */ SDK_MEM_PUB std::uint32_t m_uId;
	/* 0x0004 */ SDK_MEM_PUB std::uint16_t m_uWorldId;
	/* 0x0006 */ SDK_MEM_PRI char pad_0x6[0xE];
	/* 0x0014 */ SDK_MEM_PUB std::uint32_t m_uFilter;
	/* 0x0018 */ SDK_MEM_PRI char pad_0x18[0xC];
	/* 0x0024 */ SDK_MEM_PRI std::uint32_t m_uSomeFlag;
	/* 0x0028 */ SDK_MEM_PRI char pad_0x28[0x4];
	/* 0x002C */ SDK_MEM_PUB bool m_bWaterTrigger;
	/* 0x002D */ SDK_MEM_PRI char pad_0x2D[0x3];
	/* 0x0030 */ SDK_MEM_PUB btBoxShape* m_pBoxShape;
	/* 0x0038 */ SDK_MEM_PUB btPairCachingGhostObject* m_pGhostObject;
	/* 0x0040 */ SDK_MEM_PUB AreaTriggerProxy* m_pPhysicsProxy;
	/* 0x0048 */ SDK_MEM_PRI char pad_0x48[0x100];
	/* 0x0148 */ SDK_MEM_PUB DirectX::XMFLOAT3 m_position;
	/* 0x0154 */ SDK_MEM_PUB DirectX::XMFLOAT4 m_rotation;
	/* 0x0164 */ SDK_MEM_PUB DirectX::XMFLOAT3 m_size;
	/* 0x0170 */ SDK_MEM_PRI char pad_0x170[0x8];
}; // Size: 0x178

SMSDK_CHECK_MEMBER_OFFSET(AreaTrigger, m_uId, 0x0);
SMSDK_CHECK_MEMBER_OFFSET(AreaTrigger, m_uWorldId, 0x4);
SMSDK_CHECK_MEMBER_OFFSET(AreaTrigger, m_uFilter, 0x14);
SMSDK_CHECK_MEMBER_OFFSET(AreaTrigger, m_bWaterTrigger, 0x2C);
SMSDK_CHECK_MEMBER_OFFSET(AreaTrigger, m_pBoxShape, 0x30);
SMSDK_CHECK_MEMBER_OFFSET(AreaTrigger, m_pGhostObject, 0x38);
SMSDK_CHECK_MEMBER_OFFSET(AreaTrigger, m_pPhysicsProxy, 0x40);
SMSDK_CHECK_MEMBER_OFFSET(AreaTrigger, m_position, 0x148);
SMSDK_CHECK_MEMBER_OFFSET(AreaTrigger, m_rotation, 0x154);
SMSDK_CHECK_MEMBER_OFFSET(AreaTrigger, m_size, 0x164);
SMSDK_CHECK_STRUCT_SIZE(AreaTrigger, 0x178);

//
// AREA TRIGGER WORLD
//

struct AreaTriggerWorld
{
	/* 0x0000 */ SDK_MEM_PUB std::uint16_t m_uWorldId;
	/* 0x0002 */ SDK_MEM_PRI char pad_0x2[0x6];
	/* 0x0008 */ SDK_MEM_PUB std::map<std::uint32_t, AreaTrigger*> m_mapAreaTriggers;
	/* 0x0018 */ SDK_MEM_PUB std::vector<AreaTrigger*> m_vecAreaTriggerQueue;
	/* 0x0030 */ SDK_MEM_PRI char pad_0x30[0x18];
}; // Size: 0x48

SMSDK_CHECK_MEMBER_OFFSET(AreaTriggerWorld, m_uWorldId, 0x0);
SMSDK_CHECK_MEMBER_OFFSET(AreaTriggerWorld, m_mapAreaTriggers, 0x8);
SMSDK_CHECK_MEMBER_OFFSET(AreaTriggerWorld, m_vecAreaTriggerQueue, 0x18);
SMSDK_CHECK_STRUCT_SIZE(AreaTriggerWorld, 0x48);

//
// AREA TRIGGER MANAGER
//

struct AreaTriggerManager : public Task
{
	SDK_PUB SMSDK_API static AreaTriggerManager* GetInstance();

	/* 0x0008 */ SDK_MEM_PUB Concurrency::event m_event;
	/* 0x0050 */ SDK_MEM_PUB std::uint32_t m_uAreaTriggerIdCounter;
	/* 0x0054 */ SDK_MEM_PRI char pad_0x54[0x4];
	/* 0x0058 */ SDK_MEM_PUB std::unordered_map<std::uint16_t, AreaTriggerWorld> m_mapAreaTriggerWorlds;
	/* 0x0098 */ SDK_MEM_PUB std::vector<AreaTrigger*> m_vecAreaTriggers;
	/* 0x00B0 */ SDK_MEM_PRI char pad_0xB0[0x10];
}; // Size: 0xC0

SMSDK_CHECK_MEMBER_OFFSET(AreaTriggerManager, m_event, 0x8);
SMSDK_CHECK_MEMBER_OFFSET(AreaTriggerManager, m_uAreaTriggerIdCounter, 0x50);
SMSDK_CHECK_MEMBER_OFFSET(AreaTriggerManager, m_mapAreaTriggerWorlds, 0x58);
SMSDK_CHECK_MEMBER_OFFSET(AreaTriggerManager, m_vecAreaTriggers, 0x98);
SMSDK_CHECK_STRUCT_SIZE(AreaTriggerManager, 0xC0);

SMSDK_END_NAMESPACE