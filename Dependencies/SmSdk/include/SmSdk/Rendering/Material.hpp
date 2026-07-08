#pragma once

#include "SmSdk/d3d11_include.hpp"
#include "rend_resources.hpp"

#include <string>
#include <vector>

SMSDK_BEGIN_NAMESPACE

struct LayoutParameter
{
	/* 0x0000 */ SDK_MEM_PUB std::string m_defineString;
	/* 0x0020 */ SDK_MEM_PUB std::int8_t m_iSemanticIdx;
	/* 0x0021 */ SDK_MEM_PRI char pad_0x21[0x3];
	/* 0x0024 */ SDK_MEM_PUB DXGI_FORMAT m_format;
	/* 0x0028 */ SDK_MEM_PUB std::int8_t m_iInputSlot;
	/* 0x0029 */ SDK_MEM_PRI bool m_bSomeBool2;
	/* 0x002A */ SDK_MEM_PRI char pad_0x2A[0x6];
}; // Size: 0x30

SMSDK_CHECK_MEMBER_OFFSET(LayoutParameter, m_defineString, 0x0);
SMSDK_CHECK_MEMBER_OFFSET(LayoutParameter, m_iSemanticIdx, 0x20);
SMSDK_CHECK_MEMBER_OFFSET(LayoutParameter, m_format, 0x24);
SMSDK_CHECK_MEMBER_OFFSET(LayoutParameter, m_iInputSlot, 0x28);
SMSDK_CHECK_STRUCT_SIZE(LayoutParameter, 0x30);



class MaterialData
{
	/* 0x0000 */ SDK_MEM_PUB std::string m_vsEntry;
	/* 0x0020 */ SDK_MEM_PUB std::string m_psEntry;
	/* 0x0040 */ SDK_MEM_PUB std::string m_shaderPath;
	/* 0x0060 */ SDK_MEM_PUB std::vector<std::string> m_vecDefines;
	/* 0x0078 */ SDK_MEM_PUB std::vector<LayoutParameter> m_vecLayoutParams;
}; // Size: 0x90

SMSDK_CHECK_MEMBER_OFFSET(MaterialData, m_vsEntry, 0x0);
SMSDK_CHECK_MEMBER_OFFSET(MaterialData, m_psEntry, 0x20);
SMSDK_CHECK_MEMBER_OFFSET(MaterialData, m_shaderPath, 0x40);
SMSDK_CHECK_MEMBER_OFFSET(MaterialData, m_vecDefines, 0x60);
SMSDK_CHECK_MEMBER_OFFSET(MaterialData, m_vecLayoutParams, 0x78);
SMSDK_CHECK_STRUCT_SIZE(MaterialData, 0x90);



struct Material
{
	/* 0x0000 */ SDK_MEM_PUB MaterialData m_data;
	/* 0x0090 */ SDK_MEM_PUB rend::D3D11Layout* m_pLayout;
	/* 0x0098 */ SDK_MEM_PUB rend::D3D11ShaderProgram* m_pShaderProgram;
}; // Size: 0xA0

SMSDK_CHECK_MEMBER_OFFSET(Material, m_data, 0x0);
SMSDK_CHECK_MEMBER_OFFSET(Material, m_pLayout, 0x90);
SMSDK_CHECK_MEMBER_OFFSET(Material, m_pShaderProgram, 0x98);
SMSDK_CHECK_STRUCT_SIZE(Material, 0xA0);

SMSDK_END_NAMESPACE