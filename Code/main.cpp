#include "Utils/BufferWriter.hpp"
#include "Utils/BufferReader.hpp"
#include "Utils/Console.hpp"
#include "DllGlobals.hpp"

#include "VoiceChatSettingsTab.hpp"
#include "VoiceSettingsStorage.hpp"
#include "PlayerVoiceManager.hpp"
#include "VoiceManager.hpp"

#include <SmSdk/Gui/OptionsMenu.hpp>
#include <SmSdk/Callbacks.hpp>
#include <SmSdk/GameState.hpp>
#include <SmSdk/SmSdk.hpp>

#include <steam/steam_api.h>
#include <fmod/fmod.hpp>
#include <lz4/lz4.h>

#include <Windows.h>

#pragma comment(lib, "User32.lib")

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

	SM::OptionsMenu::AddSubMenu(
		"ProximityVoiceChat",
		"VOICE CHAT",
		[](SM::OptionsMenu*) -> bool { // A condition for create callback
			return SM::GameState::IsCurrentOrNextGameState(SM::EGameStateType::PlayState);
		},
		[]() -> SM::OptionsSubMenuBase* { // Create callback
			return new VoiceChatSettingsTab();
		}
	);

	// Perframe update stuff
	SM::Callbacks::RegisterOnRenderCallback(
		[](const float deltaTime) {
			VoiceSettingsStorage::Update(deltaTime);
			PlayerVoiceManager::Update(deltaTime);
			VoiceManager::UpdateVoiceRecording(deltaTime);
		}
	);

	SM::Callbacks::RegisterOnServerPacketCallback(VoiceManager::ServerPacketHandler);
	SM::Callbacks::RegisterOnClientPacketCallback(VoiceManager::ClientPacketHandler);

	return true;
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
		FreeLibrary(hModule);
		break;
	}

	return TRUE;
}