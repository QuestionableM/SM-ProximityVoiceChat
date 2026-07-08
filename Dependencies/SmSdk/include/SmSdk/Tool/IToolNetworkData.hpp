#pragma once

#include "SmSdk/config.hpp"

SMSDK_BEGIN_NAMESPACE

class IToolNetworkData
{
	SDK_PUB virtual ~IToolNetworkData() = default;

	/* 0x0008 */ SDK_MEM_PUB bool m_bDataChanged;
}; // Size: 0x10

SMSDK_CHECK_MEMBER_OFFSET(IToolNetworkData, m_bDataChanged, 0x8);
SMSDK_CHECK_STRUCT_SIZE(IToolNetworkData, 0x10);

SMSDK_END_NAMESPACE