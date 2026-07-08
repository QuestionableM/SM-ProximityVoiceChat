#pragma once

#include "SmSdk/boost_include.hpp"
#include "SmSdk/config.hpp"

#include "SmSdk/Base/Aligned16Base.hpp"
#include "SmSdk/Base/InputTarget.hpp"
#include "SmSdk/Player.hpp"

#include <DirectXMath.h>

#include <memory>

SMSDK_BEGIN_NAMESPACE

struct PlayerCamera
{
	/* 0x0000 */ SDK_MEM_PUB DirectX::XMFLOAT3 cam_character_pos;
	/* 0x000C */ SDK_MEM_PUB DirectX::XMFLOAT3 some_vector;
	/* 0x0018 */ SDK_MEM_PUB DirectX::XMFLOAT3 position;
	/* 0x0024 */ SDK_MEM_PUB DirectX::XMFLOAT3 direction;
	/* 0x0030 */ SDK_MEM_PUB DirectX::XMFLOAT3 up;
	/* 0x003C */ SDK_MEM_PUB DirectX::XMFLOAT3 some_vector2;
	/* 0x0048 */ SDK_MEM_PUB DirectX::XMFLOAT4 some_quat;
	/* 0x0058 */ SDK_MEM_PUB float up_offset;
	/* 0x005C */ SDK_MEM_PUB float pullback;
	/* 0x0060 */ SDK_MEM_PUB float fov;
	/* 0x0064 */ SDK_MEM_PUB float shake;
}; // Size: 0x68

SMSDK_CHECK_STRUCT_SIZE(PlayerCamera, 0x68);

class Viewer : public Aligned16Base
{
	SDK_PUB virtual ~Viewer() = default;

	/* 0x0010 */ SDK_MEM_PUB bool going_forwards;
	/* 0x0011 */ SDK_MEM_PUB bool going_backwards;
	/* 0x0012 */ SDK_MEM_PUB bool going_left;
	/* 0x0013 */ SDK_MEM_PUB bool going_right;
	/* 0x0014 */ SDK_MEM_PRI char pad_0x14[0x4];
	/* 0x0018 */ SDK_MEM_PUB double yaw;
	/* 0x0020 */ SDK_MEM_PUB double pitch;
	/* 0x0028 */ SDK_MEM_PUB double delta_yaw;
	/* 0x0030 */ SDK_MEM_PUB double delta_pitch;
	/* 0x0038 */ SDK_MEM_PUB double yaw_no_clamp;
	/* 0x0040 */ SDK_MEM_PUB double pitch_no_clamp;
	/* 0x0048 */ SDK_MEM_PUB double delta_yaw2;
	/* 0x0050 */ SDK_MEM_PUB double delta_pitch2;
	/* 0x0058 */ SDK_MEM_PRI char pad_0x58[0x8];
}; // Size: 0x60

SMSDK_CHECK_STRUCT_SIZE(Viewer, 0x60);

class Character;

class MyPlayer : public InputTarget, public Viewer
{
	REMOVE_COPY_CONSTRUCTORS(MyPlayer);

	SDK_PUB SMSDK_API static MyPlayer* GetInstance();

	SDK_PUB SMSDK_API std::shared_ptr<Character> getCharacter() const;
	SDK_PUB SMSDK_API std::shared_ptr<Player> getPlayer() const;

	SDK_PUB SMSDK_API static std::shared_ptr<Character> GetCharacter();
	SDK_PUB SMSDK_API static std::shared_ptr<Player> GetPlayer();

	SDK_PUB SMSDK_API static bool IsPlayerLocal(Player* pPlayer);

	/* 0x0070 */ SDK_MEM_PUB std::shared_ptr<Player> m_player;
	/* 0x0080 */ SDK_MEM_PUB std::int8_t m_controlCharacterSum;
	/* 0x0081 */ SDK_MEM_PRI char pad_0x81[0x3];
	/* 0x0084 */ SDK_MEM_PUB float m_walkDirectionRadians;
	/* 0x0088 */ SDK_MEM_PUB float m_fYawFloat;
	/* 0x008C */ SDK_MEM_PUB float m_fPitchFloat;
	/* 0x0090 */ SDK_MEM_PUB PlayerCamera camera;
	/* 0x00F8 */ SDK_MEM_PRI std::shared_ptr<struct Effect> m_someEffect;
	/* 0x0108 */ SDK_MEM_PRI char pad_0x108[0x28];
	/* 0x0130 */ SDK_MEM_PUB DirectX::XMMATRIX m_cameraMatrix;
	/* 0x0170 */ SDK_MEM_PUB float m_fCameraFov2;
	/* 0x0174 */ SDK_MEM_PRI char pad_0x174[0x4];
	/* 0x0178 */ SDK_MEM_PUB std::shared_ptr<struct FirstPersonHands> m_pFirstPersonHands;
	/* 0x0188 */ SDK_MEM_PRI char pad_0x188[0x38];
	/* 0x01C0 */ SDK_MEM_PUB std::shared_ptr<struct Inventory> m_pInventory;
	/* 0x01D0 */ SDK_MEM_PUB std::shared_ptr<struct ToolBox> m_pToolBox;
	/* 0x01E0 */ SDK_MEM_PUB std::shared_ptr<struct Construction> m_pConstruction;
	/* 0x01F0 */ SDK_MEM_PUB std::shared_ptr<struct Destruction> m_pDestruction;
	/* 0x0200 */ SDK_MEM_PRI char pad_0x200[0x10];
	/* 0x0210 */ SDK_MEM_PUB bool m_bIsRaycastValid;
	/* 0x0211 */ SDK_MEM_PRI char pad_0x211[0xD7];
	/* 0x02E8 */ SDK_MEM_PUB std::int32_t m_iOwnedLiftId;
	/* 0x02EC */ SDK_MEM_PRI char pad_0x2EC[0x34];
	/* 0x0320 */ SDK_MEM_PUB std::int32_t m_iCameraPullbackIdx;
	/* 0x0324 */ SDK_MEM_PRI char pad_0x324[0x4];
	/* 0x0328 */ SDK_MEM_PUB std::shared_ptr<struct AudioEvent> m_pAudioEvent;
	/* 0x0338 */ SDK_MEM_PRI char pad_0x338[0x1];
	/* 0x0339 */ SDK_MEM_PUB bool m_bIsDowned;
	/* 0x033A */ SDK_MEM_PRI char pad_0x33A[0x6];
	/* 0x0340 */ SDK_MEM_PUB boost::uuids::uuid m_selectedToolUuid;
	/* 0x0350 */ SDK_MEM_PUB std::int32_t m_iSelectedToolId;
	/* 0x0354 */ SDK_MEM_PUB boost::uuids::uuid m_prevSelectedToolUuid;
	/* 0x0364 */ SDK_MEM_PUB std::int32_t m_iPrevSelectedToolId;
	/* 0x0368 */ SDK_MEM_PRI char pad_0x368[0x8];
}; // Size: 0x370

SMSDK_CHECK_STRUCT_SIZE(MyPlayer, 0x370);

SMSDK_END_NAMESPACE