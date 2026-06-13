#include "VoiceManager.hpp"

#include <SmSdk/Gui/GuiSystemManager.hpp>
#include <SmSdk/Gui/InGameGuiManager.hpp>
#include <SmSdk/InputManager.hpp>
#include <SmSdk/GameState.hpp>
#include <SmSdk/MyPlayer.hpp>
#include <SmSdk/lz4.hpp>

#include "Utils/TextureLoader.hpp"
#include "Utils/BufferWriter.hpp"
#include "Utils/BufferReader.hpp"
#include "Utils/Console.hpp"
#include "DllGlobals.hpp"

#include "PlayerVoiceManager.hpp"

#include <steam/steam_api.h>

#include "../resource.h"

bool VoiceManager::sm_isVoiceRecording = false;

static char g_decompressedVoiceData[VC_BUFFER_SIZE];
void VoiceManager::PlayVoicePacket(const void* decompressedPacket)
{
	BufferReader v_reader(reinterpret_cast<const std::uint8_t*>(decompressedPacket));
	const std::uint32_t v_playerId = v_reader.Read<std::uint32_t>();
	const std::uint32_t v_bufferSz = v_reader.Read<std::uint32_t>();
	const std::uint8_t* v_pSoundData = reinterpret_cast<const std::uint8_t*>(decompressedPacket) + v_reader.Offset();

	PlayerVoice* v_pCurVoice = PlayerVoiceManager::GetVoice(v_playerId);
	if (!v_pCurVoice) return;

	ISteamUser* v_pSteamUser = SteamUser();

	const std::uint32_t v_optSampleRate = v_pSteamUser->GetVoiceOptimalSampleRate();
	v_pCurVoice->m_pChannel->setFrequency(float(v_optSampleRate));

	std::uint32_t v_decompVoiceSz;
	const EVoiceResult v_result = v_pSteamUser->DecompressVoice(
		v_pSoundData,
		v_bufferSz,
		g_decompressedVoiceData,
		sizeof(g_decompressedVoiceData),
		&v_decompVoiceSz,
		v_optSampleRate);

	if (v_result != k_EVoiceResultOK)
	{
		DebugErrorL("Failed to decompress the voice data from player ", v_playerId);
		return;
	}

	v_pCurVoice->push_voice(g_decompressedVoiceData, v_decompVoiceSz);
}

bool VoiceManager::ClientPacketHandler(
	SM::SteamNetworkClient* pNetworkClient,
	const std::uint64_t steamId,
	const void* packetData,
	const std::uint32_t packetDataSz)
{
	if (packetDataSz <= 0)
		return false;

	const std::uint8_t v_packetId = reinterpret_cast<const std::uint8_t*>(packetData)[0];
	if (v_packetId == C_ID_VOICE_PACKET)
	{
		VoiceManager::PlayVoicePacket(reinterpret_cast<const std::uint8_t*>(packetData) + 1);
		return true;
	}

	return false;
}

static char g_compressedServerPacket[VC_BUFFER_SIZE];
bool VoiceManager::ServerPacketHandler(
	SM::SteamNetworkServer* pNetworkServer,
	const std::uint64_t steamId,
	const void* packetData,
	const std::uint32_t packetDataSz)
{
	if (packetDataSz <= 0)
		return false;

	const std::uint8_t v_packetId = reinterpret_cast<const std::uint8_t*>(packetData)[0];
	if (v_packetId == C_ID_VOICE_PACKET)
	{
		const std::uint64_t v_localSteamId = SteamUser()->GetSteamID().ConvertToUint64();

		// Do not play the host audio to host
		if (steamId != v_localSteamId)
			VoiceManager::PlayVoicePacket(reinterpret_cast<const char*>(packetData) + 1);

		g_compressedServerPacket[0] = C_ID_VOICE_PACKET;
		const int v_compressedData = SM::Lz4::Compress(
			reinterpret_cast<const char*>(packetData) + 1,
			g_compressedServerPacket + 1,
			packetDataSz - 1,
			sizeof(g_compressedServerPacket) - 1);

		if (v_compressedData <= 0)
		{
			DebugErrorL("Could not compress packet!");
			return true;
		}

		ISteamNetworkingSockets* v_pSockets = SteamNetworkingSockets();
		if (const auto v_pNetworkSend = pNetworkServer->getNetworkSend())
		{
			for (const HSteamNetConnection v_curConnection : v_pNetworkSend->getAllConnections())
			{
				// Avoid sending the voice packets back to the player
				if (v_curConnection == steamId)
					continue;

				// Avoid sending the voice packets to the server since we are at server already
				if (v_curConnection == v_localSteamId)
					continue;

				EResult v_result = v_pSockets->SendMessageToConnection(
					v_curConnection,
					g_compressedServerPacket,
					std::uint32_t(v_compressedData) + 1,
					k_EP2PSendUnreliableNoDelay,
					nullptr);

				if (v_result != k_EResultOK)
				{
					DebugErrorL("Couldn't send the packet to ", v_curConnection);
					return true;
				}
			}
		}

		return true;
	}

	return false;
}


//////////////////////VOICE RECORDING FUNCTIONS//////////////////////


void VoiceManager::StartVoiceRecording()
{
	if (!sm_isVoiceRecording)
	{
		sm_isVoiceRecording = true;
		VoiceManager::UpdateSpeakerUiIcon();
		SteamUser()->StartVoiceRecording();
	}
}

void VoiceManager::StopVoiceRecording()
{
	if (sm_isVoiceRecording)
	{
		sm_isVoiceRecording = false;
		VoiceManager::UpdateSpeakerUiIcon();
		SteamUser()->StopVoiceRecording();
	}
}

static bool GetRecordingPointers(SM::SteamNetworkClient** ppClient, SM::Player** ppPlayer)
{
	(*ppClient) = SM::GameState::GetSteamNetworkClient();
	if (!(*ppClient)) return false;

	auto v_pSelfPlayer = SM::MyPlayer::GetPlayer();
	if (!v_pSelfPlayer) return false;

	(*ppPlayer) = v_pSelfPlayer.get();
	return true;
}

static char m_packetBuffer[VC_BUFFER_SIZE];
static char m_compressedPacket[VC_BUFFER_SIZE];
void VoiceManager::UpdateVoiceRecording()
{
	SM::SteamNetworkClient* v_network;
	SM::Player* v_player;

	if (!GetRecordingPointers(&v_network, &v_player)
		|| !v_player->characterExists()
		|| SM::GuiSystemManager::IsMouseVisible())
	{
		VoiceManager::StopVoiceRecording();
		return;
	}

	if (SM::InputManager::IsKeyHeld('V'))
		VoiceManager::StartVoiceRecording();
	else
		VoiceManager::StopVoiceRecording();

	if (!sm_isVoiceRecording)
		return;

	ISteamUser* v_pSteamUser = SteamUser();
	std::uint32_t v_bytes;

	EVoiceResult v_result = v_pSteamUser->GetAvailableVoice(&v_bytes);
	if (v_result != k_EVoiceResultOK)
	{
		DebugOutL("Voice is not recorded!");
		return;
	}

	DebugOutL("Voice is recording. Bytes available: ", v_bytes);

	constexpr std::size_t v_voiceBufferOffset = sizeof(std::uint32_t) * 2; //player id + buffer size
	v_pSteamUser->GetVoice(
		true,
		m_packetBuffer + v_voiceBufferOffset,
		sizeof(m_packetBuffer) - v_voiceBufferOffset,
		&v_bytes);

	reinterpret_cast<std::uint32_t*>(m_packetBuffer)[0] = v_player->m_uId;
	reinterpret_cast<std::uint32_t*>(m_packetBuffer)[1] = v_bytes;

	m_compressedPacket[0] = C_ID_VOICE_PACKET;
	int v_compressedSize = SM::Lz4::Compress(
		m_packetBuffer,
		m_compressedPacket + 1,
		int(v_voiceBufferOffset) + int(v_bytes), // PacketBuffer size: header + buffer
		sizeof(m_compressedPacket) - 1);

	if (v_compressedSize > 0)
	{
		const EResult v_result = SteamNetworkingSockets()->SendMessageToConnection(
			v_network->m_hostConnection,
			m_compressedPacket,
			v_compressedSize + 1,
			k_EP2PSendUnreliableNoDelay,
			nullptr);

		if (v_result != k_EResultOK)
		{
			DebugErrorL("Couldn't send the packet to server host");
		}
	}
}

////////////////UI FUNCTIONS/////////////////

void VoiceManager::CreateSpeakerImage()
{
	MyGUI::RenderManager* v_pRendMgr = MyGUI::RenderManager::getInstancePtr();
	if (v_pRendMgr->getTexture("SpeakerIcon"))
		return;

	MyGUI::ITexture* v_pNewTex = v_pRendMgr->createTexture("SpeakerIcon");
	FIBITMAP* v_fibitmap;

	TexLoader::TexLoadResult v_res = TexLoader::LoadTextureFromResource(&v_fibitmap, MAKEINTRESOURCE(IDB_PNG1), L"PNG", FIF_PNG);
	if (v_res != TexLoader::TexLoadResult_Success)
	{
		AttachDebugConsole();
		DebugErrorL(TexLoader::TexLoadResultToString(v_res));
		return;
	}

	const int v_imgWidth = int(FreeImage_GetWidth(v_fibitmap));
	const int v_imgHeight = int(FreeImage_GetHeight(v_fibitmap));
	v_pNewTex->createManual(v_imgWidth, v_imgHeight, MyGUI::TextureUsage::Write | MyGUI::TextureUsage::Static, MyGUI::PixelFormat::R8G8B8A8);

	const BYTE* v_imgBits = FreeImage_GetBits(v_fibitmap);
	void* v_pImgMem = v_pNewTex->lock(MyGUI::TextureUsage::Write);
	std::memcpy(v_pImgMem, v_imgBits, v_imgWidth * v_imgHeight * 4);
	v_pNewTex->unlock();

	FreeImage_Unload(v_fibitmap);
}

MyGUI::ImageBox* VoiceManager::GetSpeakerImageBox(MyGUI::Widget* main_panel)
{
	MyGUI::Widget* v_widget = main_panel->findWidget("SpeakerIcon");
	if (v_widget)
	{
		if (v_widget->isType<MyGUI::ImageBox>())
			return v_widget->castType<MyGUI::ImageBox>();

		return nullptr;
	}

	VoiceManager::CreateSpeakerImage();
	MyGUI::ImageBox* v_pNewImgBox = main_panel->createWidgetReal<MyGUI::ImageBox>(
		"ImageBox", MyGUI::FloatCoord(0.0f, 0.0f, 0.0f, 0.0f), MyGUI::Align::Default, "SpeakerIcon")->castType<MyGUI::ImageBox>();

	v_pNewImgBox->setVisible(false);
	v_pNewImgBox->setImageTexture("SpeakerIcon");

	return v_pNewImgBox;
}

void VoiceManager::UpdateSpeakerUiIcon()
{
	SM::InGameGuiManager* v_gui_mgr = SM::InGameGuiManager::GetInstance();
	if (!v_gui_mgr || !v_gui_mgr->m_pHudGui) return;

	MyGUI::ImageBox* v_speaker_icon = VoiceManager::GetSpeakerImageBox(v_gui_mgr->m_pHudGui->m_pMainPanel);
	if (!v_speaker_icon) return;

	MyGUI::Widget* v_main_panel = v_gui_mgr->m_pHudGui->m_pMainPanel;
	const float v_aspect_ratio = float(v_main_panel->getWidth()) / float(v_main_panel->getHeight());
	const int v_icon_sz = int(50.0f * v_aspect_ratio);
	const int v_icon_spacing = int(20.0f * v_aspect_ratio);

	v_speaker_icon->setSize(v_icon_sz, v_icon_sz);

	v_speaker_icon->setPosition(MyGUI::IntPoint(
		v_main_panel->getWidth() - v_speaker_icon->getWidth() - v_icon_spacing,
		(v_main_panel->getHeight() - v_speaker_icon->getHeight()) / 2
	));

	v_speaker_icon->setVisible(VoiceManager::sm_isVoiceRecording);
}