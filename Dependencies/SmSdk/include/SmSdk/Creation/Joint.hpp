#pragma once

#include "SmSdk/Base/NetObj.hpp"
#include "SmSdk/Util/Color.hpp"

SMSDK_BEGIN_NAMESPACE

struct Joint : public NetObj
{
	/* 0x0028 */ SDK_MEM_PRI char pad_0x28[0x10];
	/* 0x0038 */ SDK_MEM_PUB boost::uuids::uuid m_uuid;
	/* 0x0048 */ SDK_MEM_PUB Color m_color;
	/* 0x004C */ SDK_MEM_PRI char pad_0x4C[0x4];
	/* 0x0050 */ SDK_MEM_PUB std::shared_ptr<ChildShape> m_pChildShapeA;
	/* 0x0060 */ SDK_MEM_PUB std::shared_ptr<ChildShape> m_pChildShapeB;
	/* 0x0070 */ SDK_MEM_PUB DirectX::XMINT3 m_positionA;
	/* 0x007C */ SDK_MEM_PUB DirectX::XMINT3 m_positionB;
	/* 0x0088 */ SDK_MEM_PUB DirectX::XMINT3 m_zAxisA;
	/* 0x0094 */ SDK_MEM_PUB DirectX::XMINT3 m_zAxisB;
	/* 0x00A0 */ SDK_MEM_PUB DirectX::XMINT3 m_xAxisA;
	/* 0x00AC */ SDK_MEM_PUB DirectX::XMINT3 m_xAxisB;
	/* 0x00B8 */ SDK_MEM_PUB std::shared_ptr<class ControllerBase> m_pParentController;
	/* 0x00C8 */ SDK_MEM_PUB std::shared_ptr<class ControllerBase> m_pController;
	/* 0x00D8 */ SDK_MEM_PRI char pad_0xD8[0x8];
}; // Size: 0xE0

SMSDK_CHECK_MEMBER_OFFSET(Joint, m_uuid, 0x38);
SMSDK_CHECK_MEMBER_OFFSET(Joint, m_color, 0x48);
SMSDK_CHECK_MEMBER_OFFSET(Joint, m_pChildShapeA, 0x50);
SMSDK_CHECK_MEMBER_OFFSET(Joint, m_pChildShapeB, 0x60);
SMSDK_CHECK_MEMBER_OFFSET(Joint, m_positionA, 0x70);
SMSDK_CHECK_MEMBER_OFFSET(Joint, m_positionB, 0x7C);
SMSDK_CHECK_MEMBER_OFFSET(Joint, m_zAxisA, 0x88);
SMSDK_CHECK_MEMBER_OFFSET(Joint, m_zAxisB, 0x94);
SMSDK_CHECK_MEMBER_OFFSET(Joint, m_xAxisA, 0xA0);
SMSDK_CHECK_MEMBER_OFFSET(Joint, m_xAxisB, 0xAC);
SMSDK_CHECK_MEMBER_OFFSET(Joint, m_pParentController, 0xB8);
SMSDK_CHECK_MEMBER_OFFSET(Joint, m_pController, 0xC8);
SMSDK_CHECK_STRUCT_SIZE(Joint, 0xE0);

SMSDK_END_NAMESPACE