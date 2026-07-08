#pragma once

#include "SmSdk/Physics/PhysicsProxy.hpp"
#include "SmSdk/bullet_include.hpp"

SMSDK_BEGIN_NAMESPACE

class BodyJointPhysicsProxy : public PhysicsProxy
{
	/* 0x0030 */ SDK_MEM_PUB btCompoundShape m_compoundShape;
	/* 0x00B0 */ SDK_MEM_PRI char pad_0xB0[0x20];
}; // Size: 0xD0

SMSDK_CHECK_STRUCT_SIZE(BodyJointPhysicsProxy, 0xD0);

SMSDK_END_NAMESPACE