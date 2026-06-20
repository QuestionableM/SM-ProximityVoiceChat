#pragma once

#include "SmSdk/Network/SteamNetworkServer.hpp"
#include "SmSdk/Network/SteamNetworkClient.hpp"
#include <SmSdk/offsets.hpp>

#include <MyGUI.h>

#include <cstddef>
#include <cstdint>

#define VC_BUFFER_SIZE 0x20000
#define C_ID_VOICE_PACKET 123

/* VOICE PACKET STRUCTURE
	// id (1 byte)
	// player id (4 bytes) - the player that made the sound
	// buffer size (4 bytes) - the size of the compressed sound buffer
	// buffer data (buffer size) - the compressed sound buffer
*/

class VoiceManager
{
public:
	// Plays the uncompressed packet 123
	static void PlayVoicePacket(
		const void* decompressedPacket,
		const std::size_t decompressedPacketSz);

	static bool ClientPacketHandler(
		SM::SteamNetworkClient* pNetworkClient,
		const std::uint64_t steamId,
		const void* packetData,
		const std::uint32_t packetDataSz);

	static void HandleVoicePacket(
		SM::SteamNetworkServer* pNetworkServer,
		const std::uint64_t steamId,
		const void* packetData,
		const std::uint32_t packetDataSz);

	static bool ServerPacketHandler(
		SM::SteamNetworkServer* pNetworkServer,
		const std::uint64_t steamId,
		const void* packetData,
		const std::uint32_t packetDataSz);

	///VOICE RECORDING FUNCTIONS

	static void StartVoiceRecording();
	static void StopVoiceRecording();
	static void UpdateVoiceRecording();

	////UI FUNCTIONS

	static void CreateSpeakerImage();
	static MyGUI::ImageBox* GetSpeakerImageBox(MyGUI::Widget* parent, const bool canCreate = true);
	static void UpdateSpeakerUiIcon();

private:
	static bool sm_isVoiceRecording;
};