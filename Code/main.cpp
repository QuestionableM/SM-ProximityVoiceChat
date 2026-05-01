#include "Utils/BufferWriter.hpp"
#include "Utils/BufferReader.hpp"
#include "Utils/Console.hpp"
#include "DllGlobals.hpp"

#include "VoiceSettingsStorage.hpp"
#include "PlayerVoiceManager.hpp"
#include "CustomOptionsMenu.hpp"
#include "VoiceManager.hpp"

#include <SmSdk/SmSdk.hpp>
#include <SmSdk/Callbacks.hpp>

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

#if _SM_VERSION_NUM == 0x074778
#	define PVC_CUSTOM_OPTIONS_MENU_CONSTRUCTOR 0x3BCBC0
#	define PVC_CUSTOM_OPTIONS_MENU_INITIALIZE 0x3BD7F0
#elif _SM_VERSION_NUM == 0x073776
#	define PVC_CUSTOM_OPTIONS_MENU_CONSTRUCTOR 0x3BCBC0
#	define PVC_CUSTOM_OPTIONS_MENU_INITIALIZE 0x3BD7F0
#elif _SM_VERSION_NUM == 072775
#	define PVC_CUSTOM_OPTIONS_MENU_CONSTRUCTOR 0x3BCC40
#	define PVC_CUSTOM_OPTIONS_MENU_INITIALIZE 0x3BD870
#elif _SM_VERSION_NUM == 071772
#	define PVC_CUSTOM_OPTIONS_MENU_CONSTRUCTOR 0x3BCC20
#	define PVC_CUSTOM_OPTIONS_MENU_INITIALIZE 0x3BD850
#elif _SM_VERSION_NUM == 070771
#	define PVC_CUSTOM_OPTIONS_MENU_CONSTRUCTOR 0x3BCC20
#	define PVC_CUSTOM_OPTIONS_MENU_INITIALIZE 0x3BD850
#else
#	define PVC_CUSTOM_OPTIONS_MENU_CONSTRUCTOR 0x3CA740
#	define PVC_CUSTOM_OPTIONS_MENU_INITIALIZE 0x3CB570
#endif

static bool ProcessAttach(HMODULE hMod)
{
	if (!SmSdk::IsLoaded())
	{
		MessageBoxA(
			NULL,
			"SmSdk.dll is required for Proximity Voice Chat to work. Refer to the README page of Proximity Voice Chat and download SmSdk.dll\n\nPress OK to continue loading without the mod.",
			"SmSdk Not Found",
			MB_ICONWARNING | MB_OK);
		return false;
	}

	if (!SmSdk::CheckTimestamp(_SM_TIMESTAMP_074_778))
	{
		MessageBoxA(
			NULL,
			"Your game version is not supported by Proximity Voice Chat. The current version of the mod has been built for Scrap Mechanic 0.7.4.778\n\nPress OK to continue loading without the mod.",
			"Unsupported Version",
			MB_ICONWARNING);
		return false;
	}

	DllGlobals::SelfModule = hMod;

	AttachDebugConsole();

	if (MH_Initialize() != MH_OK)
	{
		DebugErrorL("Couldn't initialize minHook");
		return false;
	}

	ms_mhInitialized = true;

	const std::uintptr_t v_mod_base = std::uintptr_t(GetModuleHandle(NULL));
	if (EASY_CLASS_HOOK(PVC_CUSTOM_OPTIONS_MENU_CONSTRUCTOR, CustomOptionsMenu, Constructor) != MH_OK) return false;
	if (EASY_CLASS_HOOK(PVC_CUSTOM_OPTIONS_MENU_INITIALIZE, CustomOptionsMenu, Initialize) != MH_OK) return false;

	// Perframe update stuff
	SM::Callbacks::RegisterOnRenderCallback(
		[](const float deltaTime) {
			VoiceSettingsStorage::Update(deltaTime);
			PlayerVoiceManager::Update();
			VoiceManager::UpdateVoiceRecording();
		}
	);

	SM::Callbacks::RegisterOnServerPacketCallback(VoiceManager::ServerPacketHandler);
	SM::Callbacks::RegisterOnClientPacketCallback(VoiceManager::ClientPacketHandler);

	ms_mhHooksAttached = MH_EnableHook(MH_ALL_HOOKS) == MH_OK;
	return true;
}

static void ProcessDetach(HMODULE hmod)
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
		if (!ProcessAttach(hModule)) return FALSE;
		break;
	case DLL_PROCESS_DETACH:
		ProcessDetach(hModule);
		break;
	}

	return TRUE;
}