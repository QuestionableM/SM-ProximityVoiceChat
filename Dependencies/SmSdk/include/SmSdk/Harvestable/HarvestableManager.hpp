#pragma once

#include "SmSdk/config.hpp"
#include "SmSdk/Harvestable/Harvestable.hpp"

#include <unordered_map>
#include <memory>

SMSDK_BEGIN_NAMESPACE

class HarvestableManager
{
	REMOVE_COPY_CONSTRUCTORS(HarvestableManager);
	SDK_PUB virtual ~HarvestableManager() = default;

	SDK_PUB SMSDK_API static HarvestableManager* GetInstance();

	SDK_PUB SMSDK_API Harvestable* getHarvestable(const std::uint32_t uHvsIdx);
	SDK_PUB SMSDK_API Harvestable* GetHarvestable(const std::uint32_t uHvsIdx);

	/* 0x0008 */ SDK_MEM_PRI char pad_0x8[0x8];
	/* 0x0010 */ SDK_MEM_PUB std::unordered_map<std::uint32_t, std::shared_ptr<Harvestable>> m_mapHarvestables;
	/* 0x0050 */ SDK_MEM_PRI char pad_0x50[0x50];
	/* 0x00A0 */ SDK_MEM_PUB std::unordered_map<std::uint32_t, struct HarvestableCollision> m_mapHarvestableCollisions;
	/* 0x00E0 */ SDK_MEM_PUB std::unordered_map<boost::uuids::uuid, std::shared_ptr<struct HarvestableData>> m_mapHarvestableData;
	/* 0x0120 */ SDK_MEM_PUB std::shared_ptr<struct HarvestableData> m_pHarvestableData;
	/* 0x0130 */ SDK_MEM_PRI char pad_0x130[0x70];
}; // Size: 0x1A0

SMSDK_CHECK_STRUCT_SIZE(HarvestableManager, 0x1A0);

SMSDK_END_NAMESPACE