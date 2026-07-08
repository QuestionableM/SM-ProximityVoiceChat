#pragma once

#include "SmSdk/Physics/PhysicsProxy.hpp"
#include "SmSdk/config.hpp"

SMSDK_BEGIN_NAMESPACE

class HarvestablePhysicsProxy : public PhysicsProxy
{
	/* 0x0030 */ SDK_MEM_PUB std::int32_t m_iHarvestableId;
	/* 0x0034 */ SDK_MEM_PRI char pad_0x34[0x8C];
}; // Size: 0xC0

SMSDK_CHECK_STRUCT_SIZE(HarvestablePhysicsProxy, 0xC0);

SMSDK_END_NAMESPACE