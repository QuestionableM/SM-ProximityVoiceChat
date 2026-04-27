#pragma once

#include "SmSdk/config.hpp"

#if defined(SMSDK_BUILD_DLL)
# include <vector>
# include <mutex>
#endif

SMSDK_BEGIN_NAMESPACE

class Callbacks
{
	using OnRenderCallback = void (*)(const float deltaTime);

	// Attaches a callback that is called before a frame is drawn
	SDK_PUB SMSDK_API static void RegisterOnRenderCallback(OnRenderCallback callback);
	// Attaches a callback for server packet handler
	// Attaches a callback for client packet handler

	// DLL specific stuff that doesn't have to be exposed to the users
#if defined(SMSDK_BUILD_DLL)
	SDK_PUB static void OnRenderCallbackHandler(void* self, float deltaTime, void* a3, void* a4, void* pFrameSettings);

	SDK_PUB static bool InstallHandlers();

	SDK_PRI static std::mutex ms_mutex;
	SDK_PRI static std::vector<OnRenderCallback> ms_onRenderCallbacks;
#endif
};

SMSDK_END_NAMESPACE