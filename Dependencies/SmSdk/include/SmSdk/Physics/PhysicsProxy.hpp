#pragma once

#include "SmSdk/bullet_include.hpp"

SMSDK_BEGIN_NAMESPACE

enum class EPhysicsProxyType : std::uint8_t
{
	Limiter        = 1,
	TerrainSurface = 2,
	TerrainAsset   = 3,
	Body           = 4,
	BodyJoint      = 5,
	Lift           = 6,
	Character      = 7,
	Joint          = 8,
	Harvestable    = 9,
	Vision         = 10,
	Ragdoll        = 12,
	VoxelTerrain   = 13,
	TunnelCatcher  = 14
};

__declspec(align(16)) class PhysicsProxy
{
	SDK_PUB virtual EPhysicsProxyType getProxyType() { return EPhysicsProxyType(0); /* IMPLEMENTED BY THE GAME */ }

	/* 0x0008 */ SDK_MEM_PRI char pad_0x8[0x8];
	/* 0x0010 */ SDK_MEM_PUB btRigidBody* m_pDynamicsWorldRigidBody;
	/* 0x0018 */ SDK_MEM_PUB btRigidBody* m_pTickRaycastCollisionObject;
	/* 0x0020 */ SDK_MEM_PUB btCollisionObject* m_pInterpolatedRaycastCollisionObject;
	/* 0x0028 */ SDK_MEM_PUB std::uint16_t m_uWorldId;
	/* 0x002A */ SDK_MEM_PRI char pad_0x2A[0x6];
}; // Size: 0x30

SMSDK_CHECK_STRUCT_SIZE(PhysicsProxy, 0x30);

SMSDK_END_NAMESPACE