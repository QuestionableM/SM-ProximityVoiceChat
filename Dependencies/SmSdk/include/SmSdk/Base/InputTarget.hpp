#pragma once

#include "SmSdk/config.hpp"
#include "SmSdk/unreferenced_params.hpp"

SMSDK_BEGIN_NAMESPACE

class InputTarget
{
	SDK_PUB virtual void onKeyPress(int key) { SMSDK_UNREF(key); /* implemented by the game */ }
	SDK_PUB virtual void onKeyRelease(int key) { SMSDK_UNREF(key); /* implemented by the game */ }
	SDK_PUB virtual void onMouseKeyPress(int mouseKey) { SMSDK_UNREF(mouseKey); /* implemented by the game */ }
	SDK_PUB virtual void onMouseKeyRelease(int mouseKey) { SMSDK_UNREF(mouseKey); /* implemented by the game */ }
	SDK_PRI virtual void func5() { /* implemented by the game */ }
	SDK_PRI virtual void func6() { /* implemented by the game */ }
}; // Size: 0x8

SMSDK_CHECK_STRUCT_SIZE(InputTarget, 0x8);

SMSDK_END_NAMESPACE