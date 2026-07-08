#pragma once

#include "SmSdk/config.hpp"

#include "SmSdk/Base/NetObj.hpp"
#include <unordered_map>
#include <vector>
#include <memory>

SMSDK_BEGIN_NAMESPACE

struct PathNode : public NetObj
{
	/* 0x0028 */ SDK_MEM_PRI char pad_0x28[0x8];
	/* 0x0030 */ SDK_MEM_PUB std::int16_t m_iWorldId;
	/* 0x0032 */ SDK_MEM_PRI char pad_0x32[0x1E];
	/* 0x0050 */ SDK_MEM_PUB DirectX::XMFLOAT3 m_position;
	/* 0x005C */ SDK_MEM_PRI char pad_0x5C[0x4];
}; // Size: 0x60

SMSDK_CHECK_MEMBER_OFFSET(PathNode, m_iWorldId, 0x30);
SMSDK_CHECK_MEMBER_OFFSET(PathNode, m_position, 0x50);
SMSDK_CHECK_STRUCT_SIZE(PathNode, 0x60);

//
// PATHFINDER
//

struct Pathfinder
{
	SDK_PUB SMSDK_API static Pathfinder* GetInstance();

	/* 0x0000 */ SDK_MEM_PUB std::unordered_map<int, std::shared_ptr<PathNode>> m_mapPathNodes;
	/* 0x0040 */ SDK_MEM_PUB std::vector<std::shared_ptr<PathNode>> m_vecPathNodes;
	/* 0x0058 */ SDK_MEM_PRI char pad_0x58[0x48];
}; // Size: 0xA0

SMSDK_CHECK_MEMBER_OFFSET(Pathfinder, m_mapPathNodes, 0x0);
SMSDK_CHECK_MEMBER_OFFSET(Pathfinder, m_vecPathNodes, 0x40);
SMSDK_CHECK_STRUCT_SIZE(Pathfinder, 0xA0);

SMSDK_END_NAMESPACE