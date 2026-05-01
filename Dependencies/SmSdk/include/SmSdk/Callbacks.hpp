#pragma once

#include "SmSdk/config.hpp"
#include "SmSdk/offsets.hpp"

#if defined(SMSDK_BUILD_DLL)
# include <vector>
# include <mutex>
#endif

SMSDK_BEGIN_NAMESPACE

#if _SM_VERSION_NUM >= 070771
#	define STEAM_ID_TYPE std::uint64_t
#	define DEREF_STEAM_ID(steam_id) steam_id
#else
#	define STEAM_ID_TYPE std::uint64_t*
#	define DEREF_STEAM_ID(steam_id) *steam_id
#endif

struct SteamNetworkServer;
struct SteamNetworkClient;

class Callbacks
{
	using OnRenderCallback = void (*)(const float deltaTime);
	using ServerPacketCallback = bool (*)(SteamNetworkServer* self, const std::uint64_t steamId, const void* packetData, const std::uint32_t packetDataSz);
	using ClientPacketCallback = bool (*)(SteamNetworkClient* self, const std::uint64_t steamId, const void* packetData, const std::uint32_t packetDataSz);

	// Attaches a callback that is called before a frame is drawn
	SDK_PUB SMSDK_API static void RegisterOnRenderCallback(OnRenderCallback callback);
	// Attaches a callback for server packet handler
	SDK_PUB SMSDK_API static void RegisterOnServerPacketCallback(ServerPacketCallback callback);
	// Attaches a callback for client packet handler
	SDK_PUB SMSDK_API static void RegisterOnClientPacketCallback(ClientPacketCallback callback);

	// DLL specific stuff that doesn't have to be exposed to the users
#if defined(SMSDK_BUILD_DLL)
	SDK_PRI static void OnRenderCallbackHandler(void* self, float deltaTime, void* a3, void* a4, void* pFrameSettings);
	SDK_PRI static void OnServerPacketCallbackHandler(SteamNetworkServer* self, STEAM_ID_TYPE steamId, const void* packetData, const std::uint32_t packetDataSz);
	SDK_PRI static void OnClientPacketCallbackHandler(SteamNetworkClient* self, STEAM_ID_TYPE steamId, const void* packetData, const std::uint32_t packetDataSz, const bool someFlag);

	SDK_PUB static bool InstallHandlers();

	SDK_PRI static std::mutex ms_mutex;
	SDK_PRI static std::vector<OnRenderCallback> ms_onRenderCallbacks;
	SDK_PRI static std::vector<ServerPacketCallback> ms_onServerPacketCallbacks;
	SDK_PRI static std::vector<ClientPacketCallback> ms_onClientPacketCallbacks;
#endif
};

SMSDK_END_NAMESPACE