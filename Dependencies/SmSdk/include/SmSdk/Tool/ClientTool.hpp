#pragma once

#include "SmSdk/Tool/IToolImpl.hpp"
#include "SmSdk/Tool/Tool.hpp"
#include "SmSdk/Util/Hashing.hpp"

#include <unordered_map>
#include <string>
#include <memory>

SMSDK_BEGIN_NAMESPACE

class ClientTool;

enum AnimationFlag : std::uint32_t
{
	AnimationFlag_None = 0,
	AnimationFlag_Repeat = 1
};

struct ToolAnimationEntry
{
	ToolAnimationEntry(
		const std::string_view& animName,
		const std::string_view& nextAnim,
		const float animBegin,
		const float animEnd,
		const float animTime,
		const float animWeight,
		const float animSpeed,
		const std::uint32_t animFlags
	);

	/* 0x0000 */ SDK_MEM_PUB std::string m_animName;
	/* 0x0020 */ SDK_MEM_PUB std::string m_nextAnim;
	/* 0x0040 */ SDK_MEM_PUB float m_fAnimBegin;
	/* 0x0044 */ SDK_MEM_PUB float m_fAnimEnd;
	/* 0x0048 */ SDK_MEM_PUB float m_fAnimTime;
	/* 0x004C */ SDK_MEM_PUB float m_fWeight;
	/* 0x0050 */ SDK_MEM_PUB float m_fPlaybackSpeed;
	/* 0x0054 */ SDK_MEM_PUB std::uint32_t m_uFlags;
}; // Size: 0x58

SMSDK_CHECK_STRUCT_SIZE(ToolAnimationEntry, 0x58);

//
// TOOL ANIMATION LIST
//

struct ToolAnimationList
{
	/* 0x0000 */ SDK_MEM_PUB std::string m_toolIdle;
	/* 0x0020 */ SDK_MEM_PUB std::string m_toolIdleRelaxed;
	/* 0x0040 */ SDK_MEM_PUB std::string m_toolRunFwd;
	/* 0x0060 */ SDK_MEM_PUB std::string m_toolRunBwd;
	/* 0x0080 */ SDK_MEM_PUB std::string m_toolSprint;
	/* 0x00A0 */ SDK_MEM_PUB std::string m_toolJump;
	/* 0x00C0 */ SDK_MEM_PUB std::string m_toolJumpUp;
	/* 0x00E0 */ SDK_MEM_PUB std::string m_toolJumpDown;
	/* 0x0100 */ SDK_MEM_PUB std::string m_toolJumpLand;
	/* 0x0120 */ SDK_MEM_PUB std::string m_toolJumpLandFwd;
	/* 0x0140 */ SDK_MEM_PUB std::string m_toolJumpLandBwd;
	/* 0x0160 */ SDK_MEM_PUB std::string m_toolCrouchIdle;
	/* 0x0180 */ SDK_MEM_PUB std::string m_toolCrouchFwd;
	/* 0x01A0 */ SDK_MEM_PUB std::string m_toolCrouchBwd;
	/* 0x01C0 */ SDK_MEM_PRI std::string m_someString1;
	/* 0x01E0 */ SDK_MEM_PRI std::string m_someString2;
	/* 0x0200 */ SDK_MEM_PRI std::string m_someString3;
}; // Size: 0x220

SMSDK_CHECK_STRUCT_SIZE(ToolAnimationList, 0x220);

//
// TOOL ANIMATION DATA
//

struct ToolAnimationData
{
	SDK_PUB SMSDK_API void setAnimation(const std::string_view& name);
	SDK_PUB SMSDK_API bool hasAnimation(const std::string_view& name) const;
	SDK_PUB SMSDK_API void resetAnimation(const std::string_view& name);

	SDK_PUB SMSDK_API void addNewAnimation(
		const std::string_view& name,
		const std::string_view& startAnim,
		const std::string_view& nextAnim,
		const float animBegin = 0.0f,
		const float animEnd = 1.0f,
		const float playbackSpeed = 1.0f,
		const std::uint32_t flags = 256);

	SDK_PUB SMSDK_API void removeAnimation(const std::string_view& name);

	/* 0x0000 */ SDK_MEM_PUB ClientTool* m_pToolPtr;
	/* 0x0008 */ SDK_MEM_PUB std::unordered_map<std::string, ToolAnimationEntry, Hashing::StringHash, std::equal_to<>> m_mapAnimationData;
	/* 0x0048 */ SDK_MEM_PUB std::string m_currentAnim;
	/* 0x0068 */ SDK_MEM_PUB ToolAnimationList m_toolAnimList;
	/* 0x0288 */ SDK_MEM_PUB float m_fAnimBegin;
	/* 0x028C */ SDK_MEM_PRI char pad_0x28C[0x4];
}; // Size: 0x290

SMSDK_CHECK_STRUCT_SIZE(ToolAnimationData, 0x290);

//
// CLIENT TOOL
//

class ClientTool : public IToolImpl
{
	SDK_PUB SMSDK_API void setTpAnimation(const std::string_view& name);
	SDK_PUB SMSDK_API void setFpAnimation(const std::string_view& name);
	SDK_PUB SMSDK_API void setFpAndTpAnimation(const std::string_view& name);

	SDK_PUB SMSDK_API bool getBlockSprint() const;
	SDK_PUB SMSDK_API void setBlockSprint(const bool value);

	SDK_PUB SMSDK_API bool getInteractionTextSuppressed() const;
	SDK_PUB SMSDK_API void setInteractionTextSuppressed(const bool value);

	SDK_PUB SMSDK_API float getDispersionFraction() const;
	SDK_PUB SMSDK_API void setDispersionFraction(const float value);

	SDK_PUB SMSDK_API float getCrosshairAlpha() const;
	SDK_PUB SMSDK_API void setCrosshairAlpha(const float value);

	/* 0x0008 */ SDK_MEM_PUB ToolAnimationData m_tpAnims;
	/* 0x0298 */ SDK_MEM_PUB ToolAnimationData m_fpAnims;
	/* 0x0528 */ SDK_MEM_PUB std::shared_ptr<Tool> m_pTool;
	/* 0x0538 */ SDK_MEM_PUB bool m_blockSprint;
	/* 0x0539 */ SDK_MEM_PRI char pad_0x539[0x3];
	/* 0x053C */ SDK_MEM_PUB float m_fDispersionFraction;
	/* 0x0540 */ SDK_MEM_PUB float m_fCrosshairAlpha;
	/* 0x0544 */ SDK_MEM_PUB bool m_interactionTextSuppressed;
	/* 0x0545 */ SDK_MEM_PRI char pad_0x545[0x3];
}; // Size: 0x548

SMSDK_CHECK_STRUCT_SIZE(ClientTool, 0x548);

SMSDK_END_NAMESPACE