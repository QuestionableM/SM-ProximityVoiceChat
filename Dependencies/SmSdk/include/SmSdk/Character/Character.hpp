#pragma once

#include "SmSdk/bullet_include.hpp"
#include "SmSdk/boost_include.hpp"
#include "SmSdk/Base/NetObj.hpp"
#include "SmSdk/offsets.hpp"

#include <DirectXMath.h>

#include <vector>
#include <memory>
#include <string>

SMSDK_BEGIN_NAMESPACE

struct CharacterScriptData
{
	/* 0x0000 */ SDK_MEM_PUB bool m_bHasClientOnGraphicsLoaded;
	/* 0x0001 */ SDK_MEM_PUB bool m_bHasClientOnGraphicsUnloaded;
	/* 0x0002 */ SDK_MEM_PUB bool m_bHasClientCanInteract;
	/* 0x0003 */ SDK_MEM_PUB bool m_bHasClientOnInteract;
	/* 0x0004 */ SDK_MEM_PUB bool m_bHasClientOnProjectile;
	/* 0x0005 */ SDK_MEM_PUB bool m_bHasClientOnMelee;
	/* 0x0006 */ SDK_MEM_PUB bool m_bHasClientOnCollision;
	/* 0x0007 */ SDK_MEM_PRI char pad_0x7[0x1];
}; // Size: 0x8

SMSDK_CHECK_STRUCT_SIZE(CharacterScriptData, 0x8);

class CharacterController : public btActionInterface
{
	/* 0x0008 */ SDK_MEM_PRI char pad_0x8[0x8];
	/* 0x0010 */ SDK_MEM_PUB float m_fGroundTraction;
	/* 0x0014 */ SDK_MEM_PUB float m_fAirTraction;
	/* 0x0018 */ SDK_MEM_PRI std::int32_t m_iUnk1;
	/* 0x001C */ SDK_MEM_PRI float m_fUnk1;
	/* 0x0020 */ SDK_MEM_PRI float m_fUnk2;
	/* 0x0024 */ SDK_MEM_PUB float m_fStepOverHeight;
	/* 0x0028 */ SDK_MEM_PRI float m_fUnk3;
	/* 0x002C */ SDK_MEM_PUB float m_fGravity;
	/* 0x0030 */ SDK_MEM_PUB float m_fMass;
	/* 0x0034 */ SDK_MEM_PRI float m_fUnk4;
	/* 0x0038 */ SDK_MEM_PUB btPairCachingGhostObject* m_pPairCachingGhostObject;
	/* 0x0040 */ SDK_MEM_PUB float m_fFallVelocity;
	/* 0x0044 */ SDK_MEM_PUB float m_fFallAcceleration;
	/* 0x0048 */ SDK_MEM_PUB float m_fJumpStrength;
	/* 0x004C */ SDK_MEM_PRI float m_fUnk5;
	/* 0x0050 */ SDK_MEM_PRI char pad_0x50[0x10];
	/* 0x0060 */ SDK_MEM_PUB btVector3 m_targetMovementVelocity;
	/* 0x0070 */ SDK_MEM_PUB btVector3 m_movementVelocity;
	/* 0x0080 */ SDK_MEM_PRI char pad_0x80[0x20];
	/* 0x00A0 */ SDK_MEM_PUB btVector3 m_targetFinalWorldMovement;
	/* 0x00B0 */ SDK_MEM_PUB btVector3 m_finalWorldMovement;
	/* 0x00C0 */ SDK_MEM_PUB btVector3 m_worldMovement2;
	/* 0x00D0 */ SDK_MEM_PRI char pad_0xD0[0x40];
	/* 0x0110 */ SDK_MEM_PUB btVector3 m_surfaceNormal;
	/* 0x0120 */ SDK_MEM_PUB float m_fStepOverHeightCpy;
	/* 0x0124 */ SDK_MEM_PUB std::uint32_t m_uTicksInAir;
	/* 0x0128 */ SDK_MEM_PRI char pad_0x128[0x8];
	/* 0x0130 */ SDK_MEM_PUB std::uint8_t m_eSurfaceType;
	/* 0x0131 */ SDK_MEM_PRI char pad_0x131[0x7];
	/* 0x0138 */ SDK_MEM_PUB std::uint32_t m_uBodyId;
	/* 0x013C */ SDK_MEM_PRI char pad_0x13C[0x14];
	/* 0x0150 */ SDK_MEM_PUB btVector3 m_lastTouchedGlobalPos;
	/* 0x0160 */ SDK_MEM_PUB btVector3 m_lastTouchedLocalPos;
	/* 0x0170 */ SDK_MEM_PUB bool m_bInAir;
	/* 0x0171 */ SDK_MEM_PRI char pad_0x171[0x2F];
}; // Size: 0x1A0

SMSDK_CHECK_MEMBER_OFFSET(CharacterController, m_fGroundTraction, 0x10);
SMSDK_CHECK_MEMBER_OFFSET(CharacterController, m_fAirTraction, 0x14);
SMSDK_CHECK_MEMBER_OFFSET(CharacterController, m_fStepOverHeight, 0x24);
SMSDK_CHECK_MEMBER_OFFSET(CharacterController, m_fGravity, 0x2C);
SMSDK_CHECK_MEMBER_OFFSET(CharacterController, m_fMass, 0x30);
SMSDK_CHECK_MEMBER_OFFSET(CharacterController, m_pPairCachingGhostObject, 0x38);
SMSDK_CHECK_MEMBER_OFFSET(CharacterController, m_fFallVelocity, 0x40);
SMSDK_CHECK_MEMBER_OFFSET(CharacterController, m_fFallAcceleration, 0x44);
SMSDK_CHECK_MEMBER_OFFSET(CharacterController, m_fJumpStrength, 0x48);
SMSDK_CHECK_MEMBER_OFFSET(CharacterController, m_targetMovementVelocity, 0x60);
SMSDK_CHECK_MEMBER_OFFSET(CharacterController, m_movementVelocity, 0x70);
SMSDK_CHECK_MEMBER_OFFSET(CharacterController, m_targetFinalWorldMovement, 0xA0);
SMSDK_CHECK_MEMBER_OFFSET(CharacterController, m_finalWorldMovement, 0xB0);
SMSDK_CHECK_MEMBER_OFFSET(CharacterController, m_worldMovement2, 0xC0);
SMSDK_CHECK_MEMBER_OFFSET(CharacterController, m_surfaceNormal, 0x110);
SMSDK_CHECK_MEMBER_OFFSET(CharacterController, m_fStepOverHeightCpy, 0x120);
SMSDK_CHECK_MEMBER_OFFSET(CharacterController, m_uTicksInAir, 0x124);
SMSDK_CHECK_MEMBER_OFFSET(CharacterController, m_eSurfaceType, 0x130);
SMSDK_CHECK_MEMBER_OFFSET(CharacterController, m_uBodyId, 0x138);
SMSDK_CHECK_MEMBER_OFFSET(CharacterController, m_lastTouchedGlobalPos, 0x150);
SMSDK_CHECK_MEMBER_OFFSET(CharacterController, m_lastTouchedLocalPos, 0x160);
SMSDK_CHECK_MEMBER_OFFSET(CharacterController, m_bInAir, 0x170);
SMSDK_CHECK_STRUCT_SIZE(CharacterController, 0x1A0);

#if _SM_VERSION_NUM >= 070771
struct CharacterControllerData
{
	/* 0x0000 */ SDK_MEM_PUB float m_fWalkSpeed;
	/* 0x0004 */ SDK_MEM_PUB float m_fAimSpeed;
	/* 0x0008 */ SDK_MEM_PUB float m_fCrouchSpeed;
	/* 0x000C */ SDK_MEM_PUB float m_fSprintSpeed;
	/* 0x0010 */ SDK_MEM_PUB float m_fJumpStrength;
	/* 0x0014 */ SDK_MEM_PUB float m_fRadius;
	/* 0x0018 */ SDK_MEM_PUB float m_fHeight;
	/* 0x001C */ SDK_MEM_PUB float m_fHeightCrouch;
	/* 0x0020 */ SDK_MEM_PUB float m_fMass;
	/* 0x0024 */ SDK_MEM_PRI char pad_0x24[0xC];
	/* 0x0030 */ SDK_MEM_PUB bool m_bCanSwim;
	/* 0x0031 */ SDK_MEM_PRI char pad_0x31[0x3];
}; // Size: 0x34

SMSDK_CHECK_STRUCT_SIZE(CharacterControllerData, 0x34);

enum ECharacterMovementState : std::int8_t
{
	ECharacterMovementState_Standing = 1,
	ECharacterMovementState_Crouching = 2,
	ECharacterMovementState_Sitting = 3
};
#endif

class Character : public NetObj
{
	SDK_PUB SMSDK_API std::uint16_t getWorldId() const;
	SDK_PUB SMSDK_API std::uint64_t getOwnerSteamId() const;
	SDK_PUB SMSDK_API std::uint32_t getUnitId() const;
	SDK_PUB SMSDK_API boost::uuids::uuid getUuid() const;
	SDK_PUB SMSDK_API boost::uuids::uuid getSelectedToolUuid() const;
	SDK_PUB SMSDK_API DirectX::XMFLOAT4 getColor() const;
	SDK_PUB SMSDK_API std::string_view getNameTag() const;

	SDK_PUB SMSDK_API DirectX::XMFLOAT3 getPosition() const;
	SDK_PUB SMSDK_API DirectX::XMFLOAT3 getVelocity() const;
	SDK_PUB SMSDK_API std::shared_ptr<class CharacterGraphics> getGraphics() const;
	SDK_PUB SMSDK_API std::shared_ptr<class GuiInterface> getNameTagGui() const;

	SDK_PUB SMSDK_API float getPitch() const;
	SDK_PUB SMSDK_API float getYaw() const;

#if _SM_VERSION_NUM >= 070771
	/* 0x0028 */ SDK_MEM_PRI char pad_0x28[0x8];
	/* 0x0030 */ SDK_MEM_PUB std::uint16_t m_uWorldId;
	/* 0x0032 */ SDK_MEM_PRI char pad_0x32[0x6];
	/* 0x0038 */ SDK_MEM_PUB std::uint64_t m_uOwnerSteamId;
	/* 0x0040 */ SDK_MEM_PUB bool m_bIsPlayer;
	/* 0x0041 */ SDK_MEM_PRI char pad_0x41[0x3];
	/* 0x0044 */ SDK_MEM_PUB std::uint32_t m_uUnitId;
	/* 0x0048 */ SDK_MEM_PUB boost::uuids::uuid m_uuid;
	/* 0x0058 */ SDK_MEM_PUB bool m_bDowned;
	/* 0x0059 */ SDK_MEM_PUB bool m_bSwimming;
	/* 0x005A */ SDK_MEM_PUB bool m_bDiving;
	/* 0x005B */ SDK_MEM_PRI char pad_0x5B[0x1];
	/* 0x005C */ SDK_MEM_PUB bool m_bClimbing;
	/* 0x005D */ SDK_MEM_PUB bool m_bTumbling;
	/* 0x005E */ SDK_MEM_PRI char pad_0x5E[0x2];
	/* 0x0060 */ SDK_MEM_PUB float m_fMovementSpeedFraction;
	/* 0x0064 */ SDK_MEM_PRI char pad_0x64[0x4];
	/* 0x0068 */ SDK_MEM_PUB std::vector<std::string> m_vecAnimations;
	/* 0x0080 */ SDK_MEM_PUB DirectX::XMFLOAT3 m_spawnPosition;
	/* 0x008C */ SDK_MEM_PRI char pad_0x8C[0x1C];
	/* 0x00A8 */ SDK_MEM_PUB DirectX::XMFLOAT3 m_position;
	/* 0x00B4 */ SDK_MEM_PUB DirectX::XMFLOAT3 m_velocityDirection;
	/* 0x00C0 */ SDK_MEM_PUB DirectX::XMFLOAT3 m_velocity;
	/* 0x00CC */ SDK_MEM_PUB DirectX::XMFLOAT3 m_acceleration;
	/* 0x00D8 */ SDK_MEM_PRI char pad_0xD8[0x30];
	/* 0x0108 */ SDK_MEM_PUB float m_fWalkYaw;
	/* 0x010C */ SDK_MEM_PUB float m_fYaw;
	/* 0x0110 */ SDK_MEM_PUB float m_fPitch;
	/* 0x0114 */ SDK_MEM_PRI char pad_0x114[0x790];
	/* 0x08A4 */ SDK_MEM_PUB DirectX::XMFLOAT3 m_upDirection;
	/* 0x08B0 */ SDK_MEM_PRI char pad_0x8B0[0x8];
	/* 0x08B8 */ SDK_MEM_PUB std::int32_t m_iNextLockingInteractableId;
	/* 0x08BC */ SDK_MEM_PUB std::int32_t m_iLockingInteractableId;
	/* 0x08C0 */ SDK_MEM_PRI char pad_0x8C0[0x18];
	/* 0x08D8 */ SDK_MEM_PUB bool m_bIsOnGround;
	/* 0x08D9 */ SDK_MEM_PRI char pad_0x8D9[0x3];
	/* 0x08DC */ SDK_MEM_PUB float m_fAirTime;
	/* 0x08E0 */ SDK_MEM_PUB DirectX::XMFLOAT3 m_groundNormal;
	/* 0x08EC */ SDK_MEM_PRI char pad_0x8EC[0xC];
	/* 0x08F8 */ SDK_MEM_PUB boost::uuids::uuid m_selectedToolUuid;
	/* 0x0908 */ SDK_MEM_PUB std::int32_t m_iSelectedToolId;
	/* 0x090C */ SDK_MEM_PUB boost::uuids::uuid m_prevSelectedToolUuid;
	/* 0x091C */ SDK_MEM_PUB std::int32_t m_iPrevSelectedToolId;
	/* 0x0920 */ SDK_MEM_PRI char pad_0x920[0x2];
	/* 0x0922 */ SDK_MEM_PUB ECharacterMovementState m_charMovementState;
	/* 0x0923 */ SDK_MEM_PRI char pad_0x923[0x225];
	/* 0x0B48 */ SDK_MEM_PUB std::shared_ptr<CharacterController> m_pController;
	/* 0x0B58 */ SDK_MEM_PUB std::shared_ptr<struct CharacterPhysicsProxy> m_pPhysicsProxy;
	/* 0x0B68 */ SDK_MEM_PUB std::shared_ptr<struct RagdollPhysicsProxy> m_pRagdollPhysicsProxy;
	/* 0x0B78 */ SDK_MEM_PRI char pad_0xB78[0xAC];
	/* 0x0C24 */ SDK_MEM_PUB CharacterControllerData m_controllerData;
	/* 0x0C58 */ SDK_MEM_PUB CharacterScriptData m_scriptData;
	/* 0x0C60 */ SDK_MEM_PUB bool m_bCanSwim;
	/* 0x0C61 */ SDK_MEM_PRI char pad_0xC61[0xF];
	/* 0x0C70 */ SDK_MEM_PUB std::string m_scriptPath;
	/* 0x0C90 */ SDK_MEM_PUB std::string m_scriptClass;
	/* 0x0CB0 */ SDK_MEM_PUB std::int32_t m_iScriptRef;
	/* 0x0CB4 */ SDK_MEM_PUB std::int32_t m_iPublicDataScriptRef;
	/* 0x0CB8 */ SDK_MEM_PRI char pad_0xCB8[0x88];
	/* 0x0D40 */ SDK_MEM_PUB DirectX::XMFLOAT4 m_color;
	/* 0x0D50 */ SDK_MEM_PUB DirectX::XMFLOAT3 m_tumblingExtent;
	/* 0x0D5C */ SDK_MEM_PUB DirectX::XMFLOAT3 m_tumblingWorldPosition;
	/* 0x0D68 */ SDK_MEM_PUB DirectX::XMFLOAT4 m_tumblingWorldRotation;
	/* 0x0D78 */ SDK_MEM_PUB DirectX::XMFLOAT3 m_tumblingLinearVelocity;
	/* 0x0D84 */ SDK_MEM_PRI char pad_0xD84[0x1C];
	/* 0x0DA0 */ SDK_MEM_PUB std::string m_nameTag;
	/* 0x0DC0 */ SDK_MEM_PUB bool m_nameTagRequiresLineOfSight;
	/* 0x0DC1 */ SDK_MEM_PRI char pad_0xDC1[0x3];
	/* 0x0DC4 */ SDK_MEM_PUB DirectX::XMFLOAT4 m_nameTagColor;
	/* 0x0DD4 */ SDK_MEM_PUB float m_fNameTagFadeDistance;
	/* 0x0DD8 */ SDK_MEM_PUB float m_fNameTagRenderDistance;
	/* 0x0DDC */ SDK_MEM_PUB std::int32_t m_iNameTagUpdateCounter;
#else
	/* 0x0028 */ SDK_MEM_PRI char pad_0x28[0x8];
	/* 0x0030 */ SDK_MEM_PUB std::uint16_t m_uWorldId;
	/* 0x0032 */ SDK_MEM_PRI char pad_0x32[0x6];
	/* 0x0038 */ SDK_MEM_PUB std::uint64_t m_uOwnerSteamId;
	/* 0x0040 */ SDK_MEM_PUB bool m_bIsPlayer;
	/* 0x0041 */ SDK_MEM_PRI char pad_0x41[0x3];
	/* 0x0044 */ SDK_MEM_PUB std::uint32_t m_uUnitId;
	/* 0x0048 */ SDK_MEM_PUB boost::uuids::uuid m_uuid;
	/* 0x0058 */ SDK_MEM_PUB bool m_bIsDowned;
	/* 0x0059 */ SDK_MEM_PUB bool m_bIsSwimming;
	/* 0x005A */ SDK_MEM_PUB bool m_bIsDiving;
	/* 0x005B */ SDK_MEM_PRI char pad_0x5B[0x1];
	/* 0x005C */ SDK_MEM_PUB bool m_bIsClimbing;
	/* 0x005D */ SDK_MEM_PUB bool m_bIsTumbling;
	/* 0x005E */ SDK_MEM_PRI char pad_0x5E[0x2];
	/* 0x0060 */ SDK_MEM_PUB float m_fMovementSpeedFraction;
	/* 0x0064 */ SDK_MEM_PRI char pad_0x64[0x4];
	/* 0x0068 */ SDK_MEM_PUB std::vector<std::string> m_vecAnimations;
	/* 0x0080 */ SDK_MEM_PUB DirectX::XMFLOAT3 m_spawnPosition;
	/* 0x008C */ SDK_MEM_PRI char pad_0x8C[0x1C];
	/* 0x00A8 */ SDK_MEM_PUB DirectX::XMFLOAT3 m_velocity;
	/* 0x00B4 */ SDK_MEM_PUB DirectX::XMFLOAT3 m_acceleration;
	/* 0x00C0 */ SDK_MEM_PRI char pad_0xC0[0x14];
	/* 0x00D4 */ SDK_MEM_PUB std::int32_t m_iControlKeySum;
	/* 0x00D8 */ SDK_MEM_PUB float m_fWalkDirectionRadians;
	/* 0x00DC */ SDK_MEM_PUB float m_fYaw;
	/* 0x00E0 */ SDK_MEM_PUB float m_fPitch;
	/* 0x00E4 */ SDK_MEM_PUB float m_fYaw2;
	/* 0x00E8 */ SDK_MEM_PUB float m_fPitch2;
	/* 0x00EC */ SDK_MEM_PUB DirectX::XMFLOAT3 m_upDirectionCpy;
	/* 0x00F8 */ SDK_MEM_PUB DirectX::XMFLOAT3 m_upDirection;
	/* 0x0104 */ SDK_MEM_PUB float m_fYaw3;
	/* 0x0108 */ SDK_MEM_PUB float m_fPitch3;
	/* 0x010C */ SDK_MEM_PRI char pad_0x10C[0x4];
	/* 0x0110 */ SDK_MEM_PUB std::int32_t m_iLockingInteractableId;
	/* 0x0114 */ SDK_MEM_PRI char pad_0x114[0x1C];
	/* 0x0130 */ SDK_MEM_PUB bool m_bIsOnGround;
	/* 0x0131 */ SDK_MEM_PRI char pad_0x131[0x3];
	/* 0x0134 */ SDK_MEM_PUB float m_fAirTime;
	/* 0x0138 */ SDK_MEM_PUB DirectX::XMFLOAT3 m_groundNormal;
	/* 0x0144 */ SDK_MEM_PRI char pad_0x144[0xC];
	/* 0x0150 */ SDK_MEM_PUB boost::uuids::uuid m_selectedToolUuid;
	/* 0x0160 */ SDK_MEM_PUB std::int32_t m_iSelectedToolId;
	/* 0x0164 */ SDK_MEM_PUB boost::uuids::uuid m_prevSelectedToolUuid;
	/* 0x0174 */ SDK_MEM_PUB std::int32_t m_iPrevSelectedToolId;
	/* 0x0178 */ SDK_MEM_PRI char pad_0x178[0x2];
	/* 0x017A */ SDK_MEM_PUB std::int8_t m_iCrouchState;
	/* 0x017B */ SDK_MEM_PRI char pad_0x17B[0x1D];
	/* 0x0198 */ SDK_MEM_PUB std::shared_ptr<CharacterController> m_pController;
	/* 0x01A8 */ SDK_MEM_PUB std::shared_ptr<struct CharacterPhysicsProxy> m_pPhysicsProxy;
	/* 0x01B8 */ SDK_MEM_PUB std::shared_ptr<struct RagdollPhysicsProxy> m_pRagdollPhysicsProxy;
	/* 0x01C8 */ SDK_MEM_PRI char pad_0x1C8[0xB8];
	/* 0x0280 */ SDK_MEM_PUB float m_fWalkSpeed;
	/* 0x0284 */ SDK_MEM_PUB float m_fAimSpeed;
	/* 0x0288 */ SDK_MEM_PUB float m_fCrouchSpeed;
	/* 0x028C */ SDK_MEM_PUB float m_fSprintSpeed;
	/* 0x0290 */ SDK_MEM_PUB float m_fJumpStrength;
	/* 0x0294 */ SDK_MEM_PUB float m_fRadius;
	/* 0x0298 */ SDK_MEM_PUB float m_fHeight;
	/* 0x029C */ SDK_MEM_PUB float m_fHeightCrouch;
	/* 0x02A0 */ SDK_MEM_PUB float m_fMass;
	/* 0x02A4 */ SDK_MEM_PRI char pad_0x2A4[0xC];
	/* 0x02B0 */ SDK_MEM_PUB bool m_bCanSwim;
	/* 0x02B1 */ SDK_MEM_PRI char pad_0x2B1[0x3];
	/* 0x02B4 */ SDK_MEM_PUB CharacterScriptData m_scriptData;
	/* 0x02BC */ SDK_MEM_PRI char pad_0x2BC[0x4];
	/* 0x02C0 */ SDK_MEM_PUB std::string m_scriptPath;
	/* 0x02E0 */ SDK_MEM_PUB std::string m_scriptClass;
	/* 0x0300 */ SDK_MEM_PUB std::int32_t m_iScriptRef;
	/* 0x0304 */ SDK_MEM_PRI char pad_0x304[0x8];
	/* 0x030C */ SDK_MEM_PUB DirectX::XMFLOAT4 m_color;
	/* 0x031C */ SDK_MEM_PUB DirectX::XMFLOAT3 m_tumblingExtent;
	/* 0x0328 */ SDK_MEM_PUB DirectX::XMFLOAT3 m_tumblingWorldPosition;
	/* 0x0334 */ SDK_MEM_PUB DirectX::XMFLOAT4 m_tumblingWorldRotation;
	/* 0x0344 */ SDK_MEM_PUB DirectX::XMFLOAT3 m_tumblingLinearVelocity;
	/* 0x0350 */ SDK_MEM_PRI char pad_0x350[0x20];
	/* 0x0370 */ SDK_MEM_PUB std::string m_nameTag;
	/* 0x0390 */ SDK_MEM_PUB bool m_nameTagRequiresLineOfSight;
	/* 0x0391 */ SDK_MEM_PRI char pad_0x391[0x3];
	/* 0x0394 */ SDK_MEM_PUB DirectX::XMFLOAT4 m_nameTagColor;
	/* 0x03A4 */ SDK_MEM_PUB float m_fNameTagFadeDistance;
	/* 0x03A8 */ SDK_MEM_PUB float m_fNameTagRenderDistance;
	/* 0x03AC */ SDK_MEM_PUB std::int32_t m_iNameTagUpdateCounter;
#endif
}; // Size: 0xDE0

#if _SM_VERSION_NUM >= 070771
SMSDK_CHECK_MEMBER_OFFSET(Character, m_uWorldId, 0x30);
SMSDK_CHECK_MEMBER_OFFSET(Character, m_uOwnerSteamId, 0x38);
SMSDK_CHECK_MEMBER_OFFSET(Character, m_bIsPlayer, 0x40);
SMSDK_CHECK_MEMBER_OFFSET(Character, m_uUnitId, 0x44);
SMSDK_CHECK_MEMBER_OFFSET(Character, m_uuid, 0x48);
SMSDK_CHECK_MEMBER_OFFSET(Character, m_bDowned, 0x58);
SMSDK_CHECK_MEMBER_OFFSET(Character, m_bSwimming, 0x59);
SMSDK_CHECK_MEMBER_OFFSET(Character, m_bDiving, 0x5A);
SMSDK_CHECK_MEMBER_OFFSET(Character, m_bClimbing, 0x5C);
SMSDK_CHECK_MEMBER_OFFSET(Character, m_bTumbling, 0x5D);
SMSDK_CHECK_MEMBER_OFFSET(Character, m_fMovementSpeedFraction, 0x60);
SMSDK_CHECK_MEMBER_OFFSET(Character, m_vecAnimations, 0x68);
SMSDK_CHECK_MEMBER_OFFSET(Character, m_spawnPosition, 0x80);
SMSDK_CHECK_MEMBER_OFFSET(Character, m_position, 0xA8);
SMSDK_CHECK_MEMBER_OFFSET(Character, m_velocityDirection, 0xB4);
SMSDK_CHECK_MEMBER_OFFSET(Character, m_velocity, 0xC0);
SMSDK_CHECK_MEMBER_OFFSET(Character, m_acceleration, 0xCC);
SMSDK_CHECK_MEMBER_OFFSET(Character, m_fWalkYaw, 0x108);
SMSDK_CHECK_MEMBER_OFFSET(Character, m_fYaw, 0x10C);
SMSDK_CHECK_MEMBER_OFFSET(Character, m_fPitch, 0x110);
SMSDK_CHECK_MEMBER_OFFSET(Character, m_upDirection, 0x8A4);
SMSDK_CHECK_MEMBER_OFFSET(Character, m_iNextLockingInteractableId, 0x8B8);
SMSDK_CHECK_MEMBER_OFFSET(Character, m_iLockingInteractableId, 0x8BC);
SMSDK_CHECK_MEMBER_OFFSET(Character, m_bIsOnGround, 0x8D8);
SMSDK_CHECK_MEMBER_OFFSET(Character, m_fAirTime, 0x8DC);
SMSDK_CHECK_MEMBER_OFFSET(Character, m_groundNormal, 0x8E0);
SMSDK_CHECK_MEMBER_OFFSET(Character, m_selectedToolUuid, 0x8F8);
SMSDK_CHECK_MEMBER_OFFSET(Character, m_iSelectedToolId, 0x908);
SMSDK_CHECK_MEMBER_OFFSET(Character, m_prevSelectedToolUuid, 0x90C);
SMSDK_CHECK_MEMBER_OFFSET(Character, m_iPrevSelectedToolId, 0x91C);
SMSDK_CHECK_MEMBER_OFFSET(Character, m_charMovementState, 0x922);
SMSDK_CHECK_MEMBER_OFFSET(Character, m_pController, 0xB48);
SMSDK_CHECK_MEMBER_OFFSET(Character, m_pPhysicsProxy, 0xB58);
SMSDK_CHECK_MEMBER_OFFSET(Character, m_pRagdollPhysicsProxy, 0xB68);
SMSDK_CHECK_MEMBER_OFFSET(Character, m_controllerData, 0xC24);
SMSDK_CHECK_MEMBER_OFFSET(Character, m_scriptData, 0xC58);
SMSDK_CHECK_MEMBER_OFFSET(Character, m_bCanSwim, 0xC60);
SMSDK_CHECK_MEMBER_OFFSET(Character, m_scriptPath, 0xC70);
SMSDK_CHECK_MEMBER_OFFSET(Character, m_scriptClass, 0xC90);
SMSDK_CHECK_MEMBER_OFFSET(Character, m_iScriptRef, 0xCB0);
SMSDK_CHECK_MEMBER_OFFSET(Character, m_iPublicDataScriptRef, 0xCB4);
SMSDK_CHECK_MEMBER_OFFSET(Character, m_color, 0xD40);
SMSDK_CHECK_MEMBER_OFFSET(Character, m_tumblingExtent, 0xD50);
SMSDK_CHECK_MEMBER_OFFSET(Character, m_tumblingWorldPosition, 0xD5C);
SMSDK_CHECK_MEMBER_OFFSET(Character, m_tumblingWorldRotation, 0xD68);
SMSDK_CHECK_MEMBER_OFFSET(Character, m_tumblingLinearVelocity, 0xD78);
SMSDK_CHECK_MEMBER_OFFSET(Character, m_nameTag, 0xDA0);
SMSDK_CHECK_MEMBER_OFFSET(Character, m_nameTagRequiresLineOfSight, 0xDC0);
SMSDK_CHECK_MEMBER_OFFSET(Character, m_nameTagColor, 0xDC4);
SMSDK_CHECK_MEMBER_OFFSET(Character, m_fNameTagFadeDistance, 0xDD4);
SMSDK_CHECK_MEMBER_OFFSET(Character, m_fNameTagRenderDistance, 0xDD8);
SMSDK_CHECK_MEMBER_OFFSET(Character, m_iNameTagUpdateCounter, 0xDDC);

SMSDK_CHECK_STRUCT_SIZE(Character, 0xDE0);
#else
SMSDK_CHECK_STRUCT_SIZE(Character, 0x3B0);
#endif

SMSDK_END_NAMESPACE