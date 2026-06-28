#include "VoiceManager.hpp"

#include <SmSdk/Gui/GuiSystemManager.hpp>
#include <SmSdk/Gui/InGameGuiManager.hpp>
#include <SmSdk/Gui/HudGui2.hpp>
#include <SmSdk/Gui/ChatGui.hpp>

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
void VoiceManager::PlayVoicePacket(
	const void* decompressedPacket,
	const std::size_t decompressedPacketSz)
{
	// Discard invalid packets, make sure we are not overrunning the buffer
	if (decompressedPacketSz < (sizeof(std::uint32_t) + sizeof(std::uint32_t)))
		return;

	BufferReader v_reader(reinterpret_cast<const std::uint8_t*>(decompressedPacket));
	const std::uint32_t v_playerId = v_reader.Read<std::uint32_t>();
	const std::uint32_t v_bufferSz = v_reader.Read<std::uint32_t>();

	// Make sure the actual voice data is correct
	if (v_bufferSz != (decompressedPacketSz - v_reader.Offset()))
		return;

	PlayerVoice* v_pCurVoice = PlayerVoiceManager::GetVoice(v_playerId);
	if (!v_pCurVoice) return;

	ISteamUser* v_pSteamUser = SteamUser();
	if (!v_pSteamUser) return;

	std::uint32_t v_decompVoiceSz;
	const EVoiceResult v_result = v_pSteamUser->DecompressVoice(
		reinterpret_cast<const std::uint8_t*>(decompressedPacket) + v_reader.Offset(),
		v_bufferSz,
		g_decompressedVoiceData,
		sizeof(g_decompressedVoiceData),
		&v_decompVoiceSz,
		PVC_PLAYER_VOICE_FREQUENCY);

	if (v_result != k_EVoiceResultOK)
	{
		DebugErrorL("Failed to decompress the voice data from player ", v_playerId);
		return;
	}

	v_pCurVoice->pushVoice(g_decompressedVoiceData, v_decompVoiceSz);
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
		VoiceManager::PlayVoicePacket(reinterpret_cast<const std::uint8_t*>(packetData) + 1, packetDataSz - 1);
		return true;
	}

	return false;
}

static char g_compressedServerPacket[VC_BUFFER_SIZE];
void VoiceManager::HandleVoicePacket(
	SM::SteamNetworkServer* pNetworkServer,
	const std::uint64_t steamId,
	const void* packetData,
	const std::uint32_t packetDataSz)
{
	const std::uint64_t v_localSteamId = SteamUser()->GetSteamID().ConvertToUint64();
	if (steamId != v_localSteamId) // Do not play the host audio to host
		VoiceManager::PlayVoicePacket(reinterpret_cast<const char*>(packetData) + 1, packetDataSz - 1);

	g_compressedServerPacket[0] = C_ID_VOICE_PACKET;
	const int v_compressedData = SM::Lz4::Compress(
		reinterpret_cast<const char*>(packetData) + 1,
		g_compressedServerPacket + 1,
		packetDataSz - 1,
		sizeof(g_compressedServerPacket) - 1);

	if (v_compressedData <= 0)
	{
		DebugErrorL("Could not compress packet!");
		return;
	}

	ISteamNetworkingSockets* v_pSockets = SteamNetworkingSockets();
	if (!v_pSockets) return;

	const auto v_pNetworkSend = pNetworkServer->getNetworkSend();
	if (!v_pNetworkSend) return;

	for (const auto& v_curConnection : v_pNetworkSend->getAllConnections())
	{
		// Avoid sending the voice packets back to the player
		if (v_curConnection.first == steamId)
			continue;

		// Avoid sending the voice packets to the server since we are at server already
		if (v_curConnection.first == v_localSteamId)
			continue;

		if (v_pSockets->SendMessageToConnection(
			v_curConnection.second,
			g_compressedServerPacket,
			static_cast<std::uint32_t>(v_compressedData) + 1,
			k_EP2PSendUnreliableNoDelay,
			nullptr) != k_EResultOK)
		{
			DebugErrorL("Couldn't send the packet to: ", v_curConnection.first);
		}
	}
}

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
		VoiceManager::HandleVoicePacket(pNetworkServer, steamId, packetData, packetDataSz);
		return true;
	}

	return false;
}


//////////////////////VOICE RECORDING FUNCTIONS//////////////////////

static char m_packetBuffer[VC_BUFFER_SIZE];
static char m_compressedPacket[VC_BUFFER_SIZE];
static float m_fSpeakingTimeout = 0.0f;

void VoiceManager::StartVoiceRecording()
{
	if (!sm_isVoiceRecording)
	{
		sm_isVoiceRecording = true;
		m_fSpeakingTimeout = 0.0f;
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

void VoiceManager::UpdateVoiceRecording(const float deltaTime)
{
	auto v_pNetwork = SM::GameState::GetSteamNetworkClient();
	auto v_pLocalPlayer = SM::MyPlayer::GetPlayer();

	if (!v_pNetwork
		|| !v_pLocalPlayer
		|| !v_pLocalPlayer->characterExists()
		|| SM::GuiSystemManager::IsMouseVisible())
	{
		VoiceManager::StopVoiceRecording();
		return;
	}

	if (SM::InputManager::IsKeyHeld('V'))
		VoiceManager::StartVoiceRecording();
	else
		VoiceManager::StopVoiceRecording();


	VoiceManager::UpdateSpeakerUiIcon();
	if (!sm_isVoiceRecording) return;

	m_fSpeakingTimeout = std::max(m_fSpeakingTimeout - deltaTime, 0.0f);

	ISteamUser* v_pSteamUser = SteamUser();
	if (!v_pSteamUser) return;

	std::uint32_t v_bytes;
	EVoiceResult v_result = v_pSteamUser->GetAvailableVoice(&v_bytes);
	if (v_result != k_EVoiceResultOK) return;

	constexpr std::size_t v_voiceBufferOffset = sizeof(std::uint32_t) * 2; //player id + buffer size
	if (v_pSteamUser->GetVoice(
		true,
		m_packetBuffer + v_voiceBufferOffset,
		sizeof(m_packetBuffer) - v_voiceBufferOffset,
		&v_bytes) != k_EVoiceResultOK)
	{
		return;
	}

	m_fSpeakingTimeout = 0.15f;

	reinterpret_cast<std::uint32_t*>(m_packetBuffer)[0] = v_pLocalPlayer->m_uId;
	reinterpret_cast<std::uint32_t*>(m_packetBuffer)[1] = v_bytes;

	m_compressedPacket[0] = C_ID_VOICE_PACKET;
	const int v_compressedSize = SM::Lz4::Compress(
		m_packetBuffer,
		m_compressedPacket + 1,
		int(v_voiceBufferOffset) + int(v_bytes), // PacketBuffer size: header + buffer
		sizeof(m_compressedPacket) - 1);

	if (v_compressedSize > 0)
	{
		const EResult v_result = SteamNetworkingSockets()->SendMessageToConnection(
			v_pNetwork->getHostConnection(),
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

#define PVC_ACTIVE_SPEAKER_COLOR 1.0f, 0.815f, 0.274f
#define PVC_INACTIVE_SPEAKER_COLOR 1.0f, 1.0f, 1.0f

MyGUI::ImageBox* VoiceManager::GetSpeakerImageBox(MyGUI::Widget* parent, const bool canCreate)
{
	MyGUI::Widget* v_widget = parent->findWidget("SpeakerIcon");
	if (v_widget)
		return v_widget->castType<MyGUI::ImageBox>(false);

	if (!canCreate)
		return nullptr;

	VoiceManager::CreateSpeakerImage();
	MyGUI::ImageBox* v_pNewImgBox = parent->createWidgetReal<MyGUI::ImageBox>(
		"ImageBox", MyGUI::FloatCoord(0.0f, 0.0f, 0.0f, 0.0f), MyGUI::Align::Default, "SpeakerIcon");

	v_pNewImgBox->setVisible(false);
	v_pNewImgBox->setColour(MyGUI::Colour(PVC_ACTIVE_SPEAKER_COLOR));
	v_pNewImgBox->setImageTexture("SpeakerIcon");

	return v_pNewImgBox;
}

void VoiceManager::UpdateSpeakerUiIcon()
{
	auto v_pHudGui = SM::InGameGuiManager::GetHudGui();
	if (!v_pHudGui) return;

	MyGUI::Widget* v_pHudMainPanel = v_pHudGui->getMainPanel();
	if (!v_pHudMainPanel) return;

	MyGUI::ImageBox* v_pSpeakerIcon = VoiceManager::GetSpeakerImageBox(v_pHudMainPanel);
	if (!v_pSpeakerIcon) return;

	const float v_aspectRatio = float(v_pHudMainPanel->getWidth()) / float(v_pHudMainPanel->getHeight());
	const int v_iconSz = int(50.0f * v_aspectRatio);
	const int v_iconSpacing = int(20.0f * v_aspectRatio);

	v_pSpeakerIcon->setSize(v_iconSz, v_iconSz);
	v_pSpeakerIcon->setPosition(MyGUI::IntPoint(
		v_pHudMainPanel->getWidth() - v_pSpeakerIcon->getWidth() - v_iconSpacing,
		(v_pHudMainPanel->getHeight() - v_pSpeakerIcon->getHeight()) / 2
	));

	v_pSpeakerIcon->setColour((m_fSpeakingTimeout > 0.0f) ? MyGUI::Colour(PVC_ACTIVE_SPEAKER_COLOR) : MyGUI::Colour(PVC_INACTIVE_SPEAKER_COLOR));
	v_pSpeakerIcon->setVisible(!SM::InGameGuiManager::IsGuiHidden() && VoiceManager::sm_isVoiceRecording);
}