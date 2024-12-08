#include "Utils/BufferWriter.hpp"
#include "Utils/BufferReader.hpp"
#include "Utils/Console.hpp"
#include "DllGlobals.hpp"

#include "VoiceSettingsStorage.hpp"
#include "PlayerVoiceManager.hpp"
#include "CustomOptionsMenu.hpp"
#include "VoiceManager.hpp"

#include "SmSdk/TimestampCheck.hpp"
#include <steam/steam_api.h>
#include <fmod/fmod.hpp>
#include <lz4/lz4.h>

#include <Windows.h>
#include <MinHook.h>

#pragma comment(lib, "User32.lib")

static bool ms_mhInitialized = false;
static bool ms_mhHooksAttached = false;

#define DEFINE_HOOK(address, detour, original) \
	MH_CreateHook((LPVOID)(v_mod_base + address), (LPVOID)detour, (LPVOID*)&original)

#define EASY_HOOK(address, func_name) \
	MH_CreateHook((LPVOID)(v_mod_base + address), (LPVOID)h_ ## func_name, (LPVOID*)&o_ ## func_name)

#define EASY_CLASS_HOOK(address, class_name, func_name) \
	MH_CreateHook((LPVOID)(v_mod_base + address), (LPVOID)class_name::h_##func_name, (LPVOID*)&class_name::o_##func_name)

static void (*o_perframeUpdate)(void*, float, void*, void*, void*) = nullptr;
static void h_perframeUpdate(void* a1, float dt, void* a3, void* a4, void* pFrameSettings)
{
	VoiceSettingsStorage::Update(dt);

	PlayerVoiceManager::Update();
	VoiceManager::UpdateVoiceRecording();
	o_perframeUpdate(a1, dt, a3, a4, pFrameSettings);
}

#if _SM_VERSION_NUM == 071772
#	define PVC_CLIENT_PACKET_HANDLER 0x406AC0
#	define PVC_SERVER_PACKET_HANDLER 0x8CE770
#	define PVC_CUSTOM_OPTIONS_MENU_CONSTRUCTOR 0x3BCC20
#	define PVC_CUSTOM_OPTIONS_MENU_INITIALIZE 0x3BD850
#	define PVC_PERFRAME_UPDATE 0x6D2B00
#elif _SM_VERSION_NUM == 070771
#	define PVC_CLIENT_PACKET_HANDLER 0x406AC0
#	define PVC_SERVER_PACKET_HANDLER 0x8CE980
#	define PVC_CUSTOM_OPTIONS_MENU_CONSTRUCTOR 0x3BCC20
#	define PVC_CUSTOM_OPTIONS_MENU_INITIALIZE 0x3BD850
#	define PVC_PERFRAME_UPDATE 0x6D2D60
#else
#	define PVC_CLIENT_PACKET_HANDLER 0x416D60
#	define PVC_SERVER_PACKET_HANDLER 0x8C6380
#	define PVC_CUSTOM_OPTIONS_MENU_CONSTRUCTOR 0x3CA740
#	define PVC_CUSTOM_OPTIONS_MENU_INITIALIZE 0x3CB570
#	define PVC_PERFRAME_UPDATE 0x6D3D10
#endif

static void process_attach(HMODULE hMod)
{
	if (!SmSdk::CheckTimestamp(_SM_TIMESTAMP_071_772))
	{
		MessageBoxA(
			NULL,
			"Your game version is not supported by Proximity Voice Chat. The current version of the mod has been built for Scrap Mechanic 0.7.1.772\n\nPress OK to continue loading without the mod.",
			"Unsupported Version",
			MB_ICONWARNING);
		return;
	}

	DllGlobals::SelfModule = hMod;

	AttachDebugConsole();

	if (MH_Initialize() != MH_OK)
	{
		DebugErrorL("Couldn't initialize minHook");
		return;
	}

	ms_mhInitialized = true;

	const std::uintptr_t v_mod_base = std::uintptr_t(GetModuleHandle(NULL));
	if (EASY_CLASS_HOOK(PVC_CLIENT_PACKET_HANDLER, VoiceManager, clientPacketHandler) != MH_OK) return;
	if (EASY_CLASS_HOOK(PVC_SERVER_PACKET_HANDLER, VoiceManager, serverPacketHandler) != MH_OK) return;
	if (EASY_CLASS_HOOK(PVC_CUSTOM_OPTIONS_MENU_CONSTRUCTOR, CustomOptionsMenu, Constructor) != MH_OK) return;
	if (EASY_CLASS_HOOK(PVC_CUSTOM_OPTIONS_MENU_INITIALIZE, CustomOptionsMenu, Initialize) != MH_OK) return;
	if (EASY_HOOK(PVC_PERFRAME_UPDATE, perframeUpdate) != MH_OK) return;

	ms_mhHooksAttached = MH_EnableHook(MH_ALL_HOOKS) == MH_OK;
}

static void process_detach(HMODULE hmod)
{
	if (ms_mhInitialized)
	{
		if (ms_mhHooksAttached)
			MH_DisableHook(MH_ALL_HOOKS);

		MH_Uninitialize();
	}

	FreeLibrary(hmod);
}

BOOL APIENTRY DllMain(
	HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		process_attach(hModule);
		break;
	case DLL_PROCESS_DETACH:
		process_detach(hModule);
		break;
	}

	return TRUE;
}