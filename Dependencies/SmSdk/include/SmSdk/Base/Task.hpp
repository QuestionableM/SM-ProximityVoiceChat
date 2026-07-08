#pragma once

#include "SmSdk/config.hpp"
#include "SmSdk/unreferenced_params.hpp"

SMSDK_BEGIN_NAMESPACE

class Task
{
	SDK_PUB virtual ~Task() {}
	SDK_PUB virtual std::int64_t update(float fDeltaTime)
	{
		SMSDK_UNREF(fDeltaTime);
		return 0;
	}
}; // Size: 0x8

SMSDK_CHECK_STRUCT_SIZE(Task, 0x8);

SMSDK_END_NAMESPACE