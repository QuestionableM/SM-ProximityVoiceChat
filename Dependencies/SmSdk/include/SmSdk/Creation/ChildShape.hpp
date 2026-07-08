#pragma once

#include "SmSdk/Base/NetObj.hpp"
#include "Shape.hpp"

#include <memory>

SMSDK_BEGIN_NAMESPACE

class RigidBody;

class ChildShape : public NetObj
{
	SDK_PUB SMSDK_API std::uint32_t getCurrentIdx() const;
	SDK_PUB SMSDK_API Color getColor() const;
	// SERVER ONLY
	SDK_PUB SMSDK_API void setColor(const Color newColor);

	/* 0x0028 */ SDK_MEM_PRI char pad_0x0028[0x30];
	/* 0x0058 */ SDK_MEM_PUB std::shared_ptr<Shape> m_pShape;
	/* 0x0068 */ SDK_MEM_PRI char pad_0x0068[0x8];
	/* 0x0070 */ SDK_MEM_PUB std::uint32_t m_uCurrentIdx;
	/* 0x0074 */ SDK_MEM_PRI char pad_0x0074[0xC];
	/* 0x0080 */ SDK_MEM_PUB std::shared_ptr<RigidBody> m_pParentBody;
	/* 0x0090 */ SDK_MEM_PUB std::shared_ptr<class ControllerBase> m_pController;
	/* 0x00A0 */ SDK_MEM_PRI char pad_0x00A0[0x30];
}; // Size: 0x00D0

SMSDK_CHECK_STRUCT_SIZE(ChildShape, 0xD0);

SMSDK_END_NAMESPACE