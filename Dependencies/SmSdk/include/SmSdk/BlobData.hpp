#pragma once

#include "SmSdk/boost_include.hpp"

#include <cstdint>
#include <cstddef>

#include "SmSdk/config.hpp"

SMSDK_BEGIN_NAMESPACE

struct BlobDataKey
{
	/* 0x0000 */ SDK_MEM_PUB boost::uuids::uuid m_uuid;
	/* 0x0010 */ SDK_MEM_PUB std::uint8_t m_data[14];
	/* 0x001E */ SDK_MEM_PUB std::uint16_t m_uSize;
}; // Size: 0x20

SMSDK_CHECK_MEMBER_OFFSET(BlobDataKey, m_uuid, 0x0);
SMSDK_CHECK_MEMBER_OFFSET(BlobDataKey, m_data, 0x10);
SMSDK_CHECK_MEMBER_OFFSET(BlobDataKey, m_uSize, 0x1E);
SMSDK_CHECK_STRUCT_SIZE(BlobDataKey, 0x20);

//
// BLOB DATA
//

struct BlobData
{
	/* 0x0000 */ SDK_MEM_PUB BlobDataKey m_key;
	/* 0x0020 */ SDK_MEM_PUB std::uint16_t m_uWorldId;
	/* 0x0022 */ SDK_MEM_PUB std::uint8_t m_uFlags;
	/* 0x0023 */ SDK_MEM_PRI char pad_0x23[0x5];
	/* 0x0028 */ SDK_MEM_PUB std::uint64_t m_uSteamId;
	/* 0x0030 */ SDK_MEM_PUB std::uint32_t m_uBlobSize; // might actually be 64 bit, gotta verify this later at some point
	/* 0x0034 */ SDK_MEM_PRI char pad_0x34[0x4];
	/* 0x0038 */ SDK_MEM_PUB void* m_pBlobData;
}; // Size: 0x40

SMSDK_CHECK_MEMBER_OFFSET(BlobData, m_key, 0x0);
SMSDK_CHECK_MEMBER_OFFSET(BlobData, m_uWorldId, 0x20);
SMSDK_CHECK_MEMBER_OFFSET(BlobData, m_uFlags, 0x22);
SMSDK_CHECK_MEMBER_OFFSET(BlobData, m_uSteamId, 0x28);
SMSDK_CHECK_MEMBER_OFFSET(BlobData, m_uBlobSize, 0x30);
SMSDK_CHECK_MEMBER_OFFSET(BlobData, m_pBlobData, 0x38);
SMSDK_CHECK_STRUCT_SIZE(BlobData, 0x40);

SMSDK_END_NAMESPACE