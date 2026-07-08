#pragma once

#include "SmSdk/Creation/JointPhysicsProxy.hpp"
#include "SmSdk/Creation/RigidBody.hpp"
#include "SmSdk/Creation/Joint.hpp"
#include "SmSdk/config.hpp"

#include <unordered_map>
#include <memory>
#include <string>

SMSDK_BEGIN_NAMESPACE

struct BodyState
{
	SDK_MEM_PUB std::shared_ptr<RigidBody> m_pBody;
	SDK_MEM_PUB std::shared_ptr<struct BodyPhysicsProxy> m_pPhysicsProxy;
};

struct JointState
{
	SDK_MEM_PUB std::shared_ptr<Joint> m_pJoint;
	SDK_MEM_PUB std::shared_ptr<JointPhysicsProxy> m_pPhysicsProxy;
};

class CreationManager
{
	REMOVE_COPY_CONSTRUCTORS(CreationManager);
	SDK_PUB virtual ~CreationManager() = default;

	SDK_PUB SMSDK_API static CreationManager* GetInstance();

	SDK_PUB SMSDK_API BodyState* getBodyState(const std::uint32_t uId);
	SDK_PUB SMSDK_API JointState* getJointState(const std::uint32_t uId);

	SDK_PUB SMSDK_API static BodyState* GetBodyState(const std::uint32_t uId);
	SDK_PUB SMSDK_API static JointState* GetJointState(const std::uint32_t uId);

	/* 0x0008 */ SDK_MEM_PUB std::unordered_map<std::uint32_t, BodyState> m_mapBodyStates;
	/* 0x0048 */ SDK_MEM_PUB std::unordered_map<std::uint32_t, std::shared_ptr<ChildShape>> m_mapChildShapes;
	/* 0x0088 */ SDK_MEM_PUB std::unordered_map<std::uint32_t, JointState> m_mapJointStates;
	/* 0x00C8 */ SDK_MEM_PUB std::unordered_map<std::uint32_t, std::shared_ptr<struct ControllerEntry>> m_mapControllerStates;
	/* 0x0108 */ SDK_MEM_PUB std::unordered_map<std::uint32_t, struct CreationEntry> m_mapCreations;
	/* 0x0148 */ SDK_MEM_PRI char pad_0x148[0x118];
}; // Size: 0x260

SMSDK_CHECK_MEMBER_OFFSET(CreationManager, m_mapBodyStates, 0x8);
SMSDK_CHECK_MEMBER_OFFSET(CreationManager, m_mapChildShapes, 0x48);
SMSDK_CHECK_MEMBER_OFFSET(CreationManager, m_mapJointStates, 0x88);
SMSDK_CHECK_MEMBER_OFFSET(CreationManager, m_mapControllerStates, 0xC8);
SMSDK_CHECK_MEMBER_OFFSET(CreationManager, m_mapCreations, 0x108);
SMSDK_CHECK_STRUCT_SIZE(CreationManager, 0x260);

SMSDK_END_NAMESPACE