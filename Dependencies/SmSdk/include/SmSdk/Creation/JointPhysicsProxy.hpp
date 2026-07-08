#pragma once

#include "SmSdk/Physics/PhysicsProxy.hpp"
#include "SmSdk/bullet_include.hpp"

SMSDK_BEGIN_NAMESPACE

struct JointPhysicsProxy : public PhysicsProxy
{
	/* 0x0030 */ SDK_MEM_PRI char pad_0x30[0x8];
	/* 0x0038 */ SDK_MEM_PUB btHingeConstraint* m_pHingeConstraint;
}; // Size: 0x40

SMSDK_CHECK_STRUCT_SIZE(JointPhysicsProxy, 0x40);

SMSDK_END_NAMESPACE