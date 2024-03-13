#include "VoiceManager.hpp"

#include "SmSdk/Gui/GuiSystemManager.hpp"
#include "SmSdk/InputManager.hpp"
#include "SmSdk/GameState.hpp"
#include "SmSdk/MyPlayer.hpp"

#include "Utils/BufferWriter.hpp"
#include "Utils/BufferReader.hpp"
#include "Utils/Console.hpp"

#include "PlayerVoiceManager.hpp"

#include <steam/steam_api.h>
#include <lz4/lz4.h>


VoiceManager::fClientPacketHandler VoiceManager::o_clientPacketHandler = nullptr;
VoiceManager::fServerPacketHandler VoiceManager::o_serverPacketHandler = nullptr;
bool VoiceManager::sm_isVoiceRecording = false;



static char g_decompressedVoiceData[VC_BUFFER_SIZE];
void VoiceManager::PlayVoicePacket(char* decompressed_packet)
{
	BufferReader v_reader(decompressed_packet);
	const std::uint32_t v_player_id = v_reader.Read<std::uint32_t>();
	const std::uint32_t v_buffer_sz = v_reader.Read<std::uint32_t>();
	const char* v_sound_data = decompressed_packet + v_reader.Offset();

	PlayerVoice* v_cur_voice = PlayerVoiceManager::GetVoice(v_player_id);
	if (!v_cur_voice) return;

	ISteamUser* v_steam_user = SteamUser();

	const std::uint32_t v_opt_sample_rate = v_steam_user->GetVoiceOptimalSampleRate();
	v_cur_voice->m_pChannel->setFrequency(float(v_opt_sample_rate));

	std::uint32_t v_decomp_voice_sz;
	const EVoiceResult v_result = v_steam_user->DecompressVoice(
		v_sound_data,
		v_buffer_sz,
		g_decompressedVoiceData,
		sizeof(g_decompressedVoiceData),
		&v_decomp_voice_sz,
		v_opt_sample_rate);

	if (v_result != k_EVoiceResultOK)
	{
		DebugErrorL("Failed to decompress the voice data from player ", v_player_id);
		return;
	}

	v_cur_voice->push_voice(g_decompressedVoiceData, v_decomp_voice_sz);
}

void VoiceManager::h_clientPacketHandler(
	void* client,
	int a2,
	void* packet_data,
	int packet_size,
	char bInitialization)
{
	const std::uint8_t v_packet_id = *reinterpret_cast<char*>(packet_data);
	if (v_packet_id == C_ID_VOICE_PACKET)
	{
		VoiceManager::PlayVoicePacket(reinterpret_cast<char*>(packet_data) + 1);
		return;
	}

	o_clientPacketHandler(client, a2, packet_data, packet_size, bInitialization);
}

static char g_compressedServerPacket[VC_BUFFER_SIZE];
void VoiceManager::h_serverPacketHandler(
	NetworkServer* server,
	std::uint64_t* steam_id,
	void* packet_data,
	int packet_size)
{
	const std::uint8_t v_packet_id = *reinterpret_cast<char*>(packet_data);
	if (v_packet_id == C_ID_VOICE_PACKET)
	{
		const std::uint64_t v_local_steam_id = SteamUser()->GetSteamID().ConvertToUint64();

		//Do not play the host audio to host
		if (*steam_id != v_local_steam_id)
			VoiceManager::PlayVoicePacket(reinterpret_cast<char*>(packet_data) + 1);

		g_compressedServerPacket[0] = C_ID_VOICE_PACKET;
		int v_compressed_data = LZ4_compress_default(
			reinterpret_cast<const char*>(packet_data) + 1,
			g_compressedServerPacket + 1,
			packet_size - 1,
			sizeof(g_compressedServerPacket) - 1);

		if (v_compressed_data <= 0)
		{
			DebugErrorL("Could not compress packet!");
			return;
		}

		for (const auto& v_cur_iter : server->network_send->steam_id_to_connection)
		{
			if (v_cur_iter.first == *steam_id || v_cur_iter.first == v_local_steam_id)
				continue;

			EResult v_result = SteamNetworkingSockets()->SendMessageToConnection(
				v_cur_iter.second,
				g_compressedServerPacket,
				std::uint32_t(v_compressed_data) + 1,
				k_EP2PSendUnreliableNoDelay,
				nullptr);

			if (v_result != k_EResultOK)
			{
				DebugErrorL("Couldn't send the packet to ", v_cur_iter.first);
				return;
			}
		}

		return;
	}

	o_serverPacketHandler(server, steam_id, packet_data, packet_size);
}


//////////////////////VOICE RECORDING FUNCTIONS//////////////////////


void VoiceManager::StartVoiceRecording()
{
	if (!sm_isVoiceRecording)
	{
		sm_isVoiceRecording = true;
		SteamUser()->StartVoiceRecording();
	}
}

void VoiceManager::StopVoiceRecording()
{
	if (sm_isVoiceRecording)
	{
		sm_isVoiceRecording = false;
		SteamUser()->StopVoiceRecording();
	}
}

static bool get_recording_pointers(SteamNetworkClient** client, Player** player)
{
	*client = GameState::GetSteamNetworkClient();
	if (!(*client)) return false;

	MyPlayer* v_local_pl = MyPlayer::GetInstance();
	if (!v_local_pl || !v_local_pl->player) return false;

	*player = v_local_pl->player.get();
	return true;
}

static char m_packetBuffer[VC_BUFFER_SIZE];
static char m_compressedPacket[VC_BUFFER_SIZE];
void VoiceManager::UpdateVoiceRecording()
{
	SteamNetworkClient* v_network;
	Player* v_player;

	if (!get_recording_pointers(&v_network, &v_player)
		|| v_player->character_id == -1
		|| GuiSystemManager::IsMouseVisible())
	{
		VoiceManager::StopVoiceRecording();
		return;
	}

	if (InputManager::IsKeyHeld('V'))
		VoiceManager::StartVoiceRecording();
	else
		VoiceManager::StopVoiceRecording();

	if (!sm_isVoiceRecording)
		return;

	ISteamUser* v_steam_user = SteamUser();
	std::uint32_t v_bytes;

	if (v_steam_user->GetAvailableVoice(&v_bytes) != k_EVoiceResultOK)
		return;

	constexpr std::size_t v_voice_buffer_offset = sizeof(std::uint32_t) * 2; //player id + buffer size
	v_steam_user->GetVoice(
		true,
		m_packetBuffer + v_voice_buffer_offset,
		sizeof(m_packetBuffer) - v_voice_buffer_offset,
		&v_bytes);

	reinterpret_cast<std::uint32_t*>(m_packetBuffer)[0] = v_player->id;
	reinterpret_cast<std::uint32_t*>(m_packetBuffer)[1] = v_bytes;

	m_compressedPacket[0] = C_ID_VOICE_PACKET;
	int v_compressed_size = LZ4_compress_default(
		m_packetBuffer,
		m_compressedPacket + 1,
		int(v_voice_buffer_offset) + int(v_bytes), //PacketBuffer size: header + buffer
		sizeof(m_compressedPacket) - 1);

	if (v_compressed_size > 0)
	{
		const EResult v_result = SteamNetworkingSockets()->SendMessageToConnection(
			v_network->host_connection,
			m_compressedPacket,
			v_compressed_size + 1,
			k_EP2PSendUnreliableNoDelay,
			nullptr);

		if (v_result != k_EResultOK)
		{
			DebugErrorL("Couldn't send the packet to server host");
		}
	}
}