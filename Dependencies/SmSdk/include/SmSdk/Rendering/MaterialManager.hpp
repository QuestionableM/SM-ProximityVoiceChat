#pragma once

#include "SmSdk/jsoncpp_include.hpp"
#include "SmSdk/config.hpp"

#include "SmSdk/Rendering/Material.hpp"

#include <unordered_map>
#include <vector>

SMSDK_BEGIN_NAMESPACE

struct MaterialEntry
{
	/* 0x0000 */ SDK_MEM_PUB std::uint32_t m_uId;
	/* 0x0004 */ SDK_MEM_PRI char pad_0x4[0x4];
	/* 0x0008 */ SDK_MEM_PUB std::string m_name;
	/* 0x0028 */ SDK_MEM_PUB std::uint8_t m_uMaterialType;
	/* 0x0029 */ SDK_MEM_PRI char pad_0x29[0x3];
	/* 0x002C */ SDK_MEM_PUB std::uint32_t m_uPipelineFlags;
	/* 0x0030 */ SDK_MEM_PUB std::uint64_t m_uRendQueueMask;
	/* 0x0038 */ SDK_MEM_PUB std::uint64_t m_uSemantic;
	/* 0x0040 */ SDK_MEM_PUB std::uint32_t m_uPosAnimCount;
	/* 0x0044 */ SDK_MEM_PUB std::uint32_t m_uVertexStride;
	/* 0x0048 */ SDK_MEM_PUB std::uint32_t m_uInstanceStride;
	/* 0x004C */ SDK_MEM_PRI char pad_0x4C[0x4];
	/* 0x0050 */ SDK_MEM_PUB Json::Value m_jCustomData;
	/* 0x0068 */ SDK_MEM_PUB Material* m_arrMaterials[132];
}; // Size: 0x488

SMSDK_CHECK_MEMBER_OFFSET(MaterialEntry, m_uId, 0x0);
SMSDK_CHECK_MEMBER_OFFSET(MaterialEntry, m_name, 0x8);
SMSDK_CHECK_MEMBER_OFFSET(MaterialEntry, m_uMaterialType, 0x28);
SMSDK_CHECK_MEMBER_OFFSET(MaterialEntry, m_uPipelineFlags, 0x2C);
SMSDK_CHECK_MEMBER_OFFSET(MaterialEntry, m_uRendQueueMask, 0x30);
SMSDK_CHECK_MEMBER_OFFSET(MaterialEntry, m_uSemantic, 0x38);
SMSDK_CHECK_MEMBER_OFFSET(MaterialEntry, m_uPosAnimCount, 0x40);
SMSDK_CHECK_MEMBER_OFFSET(MaterialEntry, m_uVertexStride, 0x44);
SMSDK_CHECK_MEMBER_OFFSET(MaterialEntry, m_uInstanceStride, 0x48);
SMSDK_CHECK_MEMBER_OFFSET(MaterialEntry, m_jCustomData, 0x50);
SMSDK_CHECK_MEMBER_OFFSET(MaterialEntry, m_arrMaterials, 0x68);
SMSDK_CHECK_STRUCT_SIZE(MaterialEntry, 0x488);

//
// MATERIAL MANAGER
//

struct MaterialManager
{
	/* 0x0000 */ SDK_MEM_PUB Material* m_pForwardParticles;
	/* 0x0008 */ SDK_MEM_PUB Material* m_pPostFxaa;
	/* 0x0010 */ SDK_MEM_PUB Material* m_pPostGodrays;
	/* 0x0018 */ SDK_MEM_PUB Material* m_pMainClutterImpostorGBuffer;
	/* 0x0020 */ SDK_MEM_PUB Material* m_pMainClutterGBuffer;
	/* 0x0028 */ SDK_MEM_PUB Material* m_pMainDebugDrawer;
	/* 0x0030 */ SDK_MEM_PUB Material* m_pGuiBlurryBackground;
	/* 0x0038 */ SDK_MEM_PUB Material* m_pGuiTextureBoxArray;
	/* 0x0040 */ SDK_MEM_PUB Material* m_pCubeMapComposition;
	/* 0x0048 */ SDK_MEM_PUB Material* m_pPostBloom;
	/* 0x0050 */ SDK_MEM_PUB Material* m_pPostAddBloom;
	/* 0x0058 */ SDK_MEM_PUB Material* m_pPostAddBloomNoise;
	/* 0x0060 */ SDK_MEM_PUB Material* m_pPostBlur;
	/* 0x0068 */ SDK_MEM_PUB Material* m_pPostSmartBlur;
	/* 0x0070 */ SDK_MEM_PUB Material* m_pPostDof;
	/* 0x0078 */ SDK_MEM_PUB Material* m_pPostCopy;
	/* 0x0080 */ SDK_MEM_PUB Material* m_pPostCopyDepth;
	/* 0x0088 */ SDK_MEM_PUB Material* m_pPostCopyBrightness;
	/* 0x0090 */ SDK_MEM_PUB Material* m_pMainTerrainSurfaceGBuffer;
	/* 0x0098 */ SDK_MEM_PUB Material* m_pMainTerrainSurfaceDepth;
	/* 0x00A0 */ SDK_MEM_PUB Material* m_pMainEditorTerrainSurfaceGBuffer;
	/* 0x00A8 */ SDK_MEM_PUB Material* m_pMainEditorTerrainSurfaceDepth;
	/* 0x00B0 */ SDK_MEM_PUB Material* m_pMainSky;
	/* 0x00B8 */ SDK_MEM_PUB Material* m_pMainImpostorGBuffer;
	/* 0x00C0 */ SDK_MEM_PUB Material* m_pMainImpostorDepth;
	/* 0x00C8 */ SDK_MEM_PUB std::unordered_map<size_t, MaterialEntry*, PassthroughHash> m_arrMaterialMap[10];
	/* 0x0348 */ SDK_MEM_PUB std::vector<MaterialEntry*> m_vecMaterials;
}; // Size: 0x360

SMSDK_CHECK_MEMBER_OFFSET(MaterialManager, m_pForwardParticles, 0x0);
SMSDK_CHECK_MEMBER_OFFSET(MaterialManager, m_pPostFxaa, 0x8);
SMSDK_CHECK_MEMBER_OFFSET(MaterialManager, m_pPostGodrays, 0x10);
SMSDK_CHECK_MEMBER_OFFSET(MaterialManager, m_pMainClutterImpostorGBuffer, 0x18);
SMSDK_CHECK_MEMBER_OFFSET(MaterialManager, m_pMainClutterGBuffer, 0x20);
SMSDK_CHECK_MEMBER_OFFSET(MaterialManager, m_pMainDebugDrawer, 0x28);
SMSDK_CHECK_MEMBER_OFFSET(MaterialManager, m_pGuiBlurryBackground, 0x30);
SMSDK_CHECK_MEMBER_OFFSET(MaterialManager, m_pGuiTextureBoxArray, 0x38);
SMSDK_CHECK_MEMBER_OFFSET(MaterialManager, m_pCubeMapComposition, 0x40);
SMSDK_CHECK_MEMBER_OFFSET(MaterialManager, m_pPostBloom, 0x48);
SMSDK_CHECK_MEMBER_OFFSET(MaterialManager, m_pPostAddBloom, 0x50);
SMSDK_CHECK_MEMBER_OFFSET(MaterialManager, m_pPostAddBloomNoise, 0x58);
SMSDK_CHECK_MEMBER_OFFSET(MaterialManager, m_pPostBlur, 0x60);
SMSDK_CHECK_MEMBER_OFFSET(MaterialManager, m_pPostSmartBlur, 0x68);
SMSDK_CHECK_MEMBER_OFFSET(MaterialManager, m_pPostDof, 0x70);
SMSDK_CHECK_MEMBER_OFFSET(MaterialManager, m_pPostCopy, 0x78);
SMSDK_CHECK_MEMBER_OFFSET(MaterialManager, m_pPostCopyDepth, 0x80);
SMSDK_CHECK_MEMBER_OFFSET(MaterialManager, m_pPostCopyBrightness, 0x88);
SMSDK_CHECK_MEMBER_OFFSET(MaterialManager, m_pMainTerrainSurfaceGBuffer, 0x90);
SMSDK_CHECK_MEMBER_OFFSET(MaterialManager, m_pMainTerrainSurfaceDepth, 0x98);
SMSDK_CHECK_MEMBER_OFFSET(MaterialManager, m_pMainEditorTerrainSurfaceGBuffer, 0xA0);
SMSDK_CHECK_MEMBER_OFFSET(MaterialManager, m_pMainEditorTerrainSurfaceDepth, 0xA8);
SMSDK_CHECK_MEMBER_OFFSET(MaterialManager, m_pMainSky, 0xB0);
SMSDK_CHECK_MEMBER_OFFSET(MaterialManager, m_pMainImpostorGBuffer, 0xB8);
SMSDK_CHECK_MEMBER_OFFSET(MaterialManager, m_pMainImpostorDepth, 0xC0);
SMSDK_CHECK_MEMBER_OFFSET(MaterialManager, m_arrMaterialMap, 0xC8);
SMSDK_CHECK_MEMBER_OFFSET(MaterialManager, m_vecMaterials, 0x348);
SMSDK_CHECK_STRUCT_SIZE(MaterialManager, 0x360);

SMSDK_END_NAMESPACE