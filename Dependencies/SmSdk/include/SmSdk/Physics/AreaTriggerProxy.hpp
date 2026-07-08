#pragma once

#include "SmSdk/Physics/PhysicsProxy.hpp"

SMSDK_BEGIN_NAMESPACE

struct AreaTriggerProxy : public PhysicsProxy
{
	/* 0x0030 */ SDK_MEM_PUB std::int32_t m_iAreaTriggerId;
	/* 0x0034 */ SDK_MEM_PRI char pad_0x34[0xC];
}; // Size: 0x40

SMSDK_CHECK_MEMBER_OFFSET(AreaTriggerProxy, m_iAreaTriggerId, 0x30);
SMSDK_CHECK_STRUCT_SIZE(AreaTriggerProxy, 0x40);

//
// WATER AREA TRIGGER PROXY
//

struct WaterAreaTriggerProxy : public AreaTriggerProxy
{
}; // Size: 0x40

SMSDK_CHECK_STRUCT_SIZE(WaterAreaTriggerProxy, 0x40);

SMSDK_END_NAMESPACE