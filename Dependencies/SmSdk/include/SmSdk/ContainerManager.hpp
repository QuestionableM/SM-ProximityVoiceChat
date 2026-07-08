#pragma once

#include "SmSdk/boost_include.hpp"
#include <unordered_map>

SMSDK_BEGIN_NAMESPACE

struct ContainerEntry
{
	/* 0x0000 */ SDK_MEM_PUB boost::uuids::uuid m_itemUuid;
	/* 0x0010 */ SDK_MEM_PUB std::int32_t m_iItemId;
	/* 0x0014 */ SDK_MEM_PUB std::int32_t m_iItemQuantity;
}; // Size: 0x18

SMSDK_CHECK_MEMBER_OFFSET(ContainerEntry, m_itemUuid, 0x0);
SMSDK_CHECK_MEMBER_OFFSET(ContainerEntry, m_iItemId, 0x10);
SMSDK_CHECK_MEMBER_OFFSET(ContainerEntry, m_iItemQuantity, 0x14);
SMSDK_CHECK_STRUCT_SIZE(ContainerEntry, 0x18);

struct ContainerItems
{
	/* 0x0000 */ SDK_MEM_PUB std::uint16_t m_uMaxStackSize;
	/* 0x0002 */ SDK_MEM_PRI char pad_0x2[0x6];
	/* 0x0008 */ SDK_MEM_PUB std::vector<ContainerEntry> m_vecEntries;
}; // Size: 0x20

SMSDK_CHECK_MEMBER_OFFSET(ContainerItems, m_uMaxStackSize, 0x0);
SMSDK_CHECK_MEMBER_OFFSET(ContainerItems, m_vecEntries, 0x8);
SMSDK_CHECK_STRUCT_SIZE(ContainerItems, 0x20);

//
// CONTAINER 2
//

struct Container2 : public NetObj
{
	/* 0x0028 */ SDK_MEM_PRI char pad_0x28[0x8];
	/* 0x0030 */ SDK_MEM_PUB ContainerItems m_clientItems;
	/* 0x0050 */ SDK_MEM_PUB ContainerItems m_serverItems;
	/* 0x0070 */ SDK_MEM_PUB ContainerItems m_containerItems3;
	/* 0x0090 */ SDK_MEM_PRI char pad_0x90[0x4];
	/* 0x0094 */ SDK_MEM_PUB std::int32_t m_iUpdateCounter;
	/* 0x0098 */ SDK_MEM_PUB std::int32_t m_iLastUpdateTick;
	/* 0x009C */ SDK_MEM_PRI char pad_0x9C[0x34];
	/* 0x00D0 */ SDK_MEM_PUB std::vector<boost::uuids::uuid> m_vecFilters;
	/* 0x00E8 */ SDK_MEM_PUB bool m_bAllowSpend;
	/* 0x00E9 */ SDK_MEM_PRI char pad_0xE9[0x7];
}; // Size: 0xF0

SMSDK_CHECK_MEMBER_OFFSET(Container2, m_clientItems, 0x30);
SMSDK_CHECK_MEMBER_OFFSET(Container2, m_serverItems, 0x50);
SMSDK_CHECK_MEMBER_OFFSET(Container2, m_containerItems3, 0x70);
SMSDK_CHECK_MEMBER_OFFSET(Container2, m_iUpdateCounter, 0x94);
SMSDK_CHECK_MEMBER_OFFSET(Container2, m_iLastUpdateTick, 0x98);
SMSDK_CHECK_MEMBER_OFFSET(Container2, m_vecFilters, 0xD0);
SMSDK_CHECK_MEMBER_OFFSET(Container2, m_bAllowSpend, 0xE8);
SMSDK_CHECK_STRUCT_SIZE(Container2, 0xF0);

//
// CONTAINER MANAGER
//

struct ContainerManager
{
	SDK_PUB SMSDK_API static ContainerManager* GetInstance();

	/* 0x0000 */ SDK_MEM_PRI char pad_0x0[0x28];
	/* 0x0028 */ SDK_MEM_PUB bool m_bOngoingTransaction;
	/* 0x0029 */ SDK_MEM_PRI char pad_0x29[0x7];
	/* 0x0030 */ SDK_MEM_PRI std::shared_ptr<Container2> m_pSomeContainer;
	/* 0x0040 */ SDK_MEM_PUB std::unordered_map<int, std::shared_ptr<Container2>> m_worldContainerMap; // NOTE: this naming inconsistency is intentional to match the original binary
	/* 0x0080 */ SDK_MEM_PRI char pad_0x80[0x18];
}; // Size: 0x98

SMSDK_CHECK_MEMBER_OFFSET(ContainerManager, m_bOngoingTransaction, 0x28);
SMSDK_CHECK_MEMBER_OFFSET(ContainerManager, m_worldContainerMap, 0x40);
SMSDK_CHECK_STRUCT_SIZE(ContainerManager, 0x98);

SMSDK_END_NAMESPACE