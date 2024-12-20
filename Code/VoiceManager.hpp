#pragma once

#include "SmSdk/Network/NetworkServer.hpp"
#include <SmSdk/offsets.hpp>

#include <MyGUI.h>

#include <cstddef>
#include <cstdint>

#define VC_BUFFER_SIZE 0x7FFFF
#define C_ID_VOICE_PACKET 123

/* VOICE PACKET STRUCTURE

	//id (1 byte)
	//player id (4 bytes) - the player that made the sound
	//buffer size (4 bytes) - the size of the compressed sound buffer
	//buffer data (buffer size) - the compressed sound buffer
*/

#if _SM_VERSION_NUM >= 070771
#	define STEAM_ID_TYPE std::uint64_t
#	define DEREF_STEAM_ID(steam_id) steam_id
#else
#	define STEAM_ID_TYPE std::uint64_t*
#	define DEREF_STEAM_ID(steam_id) *steam_id
#endif

class VoiceManager
{
public:
	using fClientPacketHandler = void (*)(void*, int, void*, int, char);
	using fServerPacketHandler = void (*)(
		NetworkServer*,
		STEAM_ID_TYPE,
		void*,
		int
	);

	///PACKET PROCESSING FUNCTIONS

	static fClientPacketHandler o_clientPacketHandler;
	static fServerPacketHandler o_serverPacketHandler;

	//Plays the uncompressed packet 123
	static void PlayVoicePacket(char* decompressed_packet);

	static void h_clientPacketHandler(
		void* client,
		int a2,
		void* packet_data,
		int packet_size,
		char bInitialization);

	static void h_serverPacketHandler(
		NetworkServer* server,
		STEAM_ID_TYPE steam_id,
		void* packet_data,
		int packet_size);

	///VOICE RECORDING FUNCTIONS

	static void StartVoiceRecording();
	static void StopVoiceRecording();
	static void UpdateVoiceRecording();

	////UI FUNCTIONS

	static void CreateSpeakerImage();
	static MyGUI::ImageBox* GetSpeakerImageBox(MyGUI::Widget* main_panel);
	static void UpdateSpeakerUiIcon();

private:
	static bool sm_isVoiceRecording;
};