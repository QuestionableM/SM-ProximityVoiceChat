#pragma once

#include "SmSdk/d3d11_include.hpp"
#include "SmSdk/config.hpp"

#include <unordered_map>
#include <string>

SMSDK_BEGIN_NAMESPACE

namespace rend
{
class D3D11Resource
{
	SDK_PRI virtual void func1() { /* implemented by the game */ }
	SDK_PRI virtual void func2() { /* implemented by the game */ }
	SDK_PRI virtual void func3() { /* implemented by the game */ }
	SDK_PRI virtual void func4() { /* implemented by the game */ }

	/* 0x0008 */ SDK_MEM_PUB std::string m_debugName;
}; // Size: 0x28

SMSDK_CHECK_MEMBER_OFFSET(rend::D3D11Resource, m_debugName, 0x8);
SMSDK_CHECK_STRUCT_SIZE(rend::D3D11Resource, 0x28);



class D3D11ShaderProgram : public rend::D3D11Resource
{
	/* 0x0028 */ SDK_MEM_PUB ID3DBlob* m_pVertexShaderBlob;
	/* 0x0030 */ SDK_MEM_PUB ID3DBlob* m_pPixelShaderBlob;
	/* 0x0038 */ SDK_MEM_PUB std::uint32_t m_uVertexShaderBlobSize;
	/* 0x003C */ SDK_MEM_PUB std::uint32_t m_uPixelShaderBlobSize;
	/* 0x0040 */ SDK_MEM_PUB ID3D11PixelShader* m_pPixelShader;
	/* 0x0048 */ SDK_MEM_PUB ID3D11VertexShader* m_pVertexShader;
	/* 0x0050 */ SDK_MEM_PUB std::string m_shaderPath;
	/* 0x0070 */ SDK_MEM_PUB std::string m_vsEntry;
	/* 0x0090 */ SDK_MEM_PUB std::string m_psEntry;
	/* 0x00B0 */ SDK_MEM_PUB std::unordered_map<XXHStringHash, std::uint32_t> m_mapPixelShaderBindings;
	/* 0x00F0 */ SDK_MEM_PUB std::unordered_map<XXHStringHash, std::uint32_t> m_mapVertexShaderBindings;
	/* 0x0130 */ SDK_MEM_PUB std::uint64_t m_uInputDescHash;
	/* 0x0138 */ SDK_MEM_PUB std::vector<std::string> m_vecDefines;
}; // Size: 0x150

SMSDK_CHECK_MEMBER_OFFSET(rend::D3D11ShaderProgram, m_pVertexShaderBlob, 0x28);
SMSDK_CHECK_MEMBER_OFFSET(rend::D3D11ShaderProgram, m_pPixelShaderBlob, 0x30);
SMSDK_CHECK_MEMBER_OFFSET(rend::D3D11ShaderProgram, m_uVertexShaderBlobSize, 0x38);
SMSDK_CHECK_MEMBER_OFFSET(rend::D3D11ShaderProgram, m_uPixelShaderBlobSize, 0x3C);
SMSDK_CHECK_MEMBER_OFFSET(rend::D3D11ShaderProgram, m_pPixelShader, 0x40);
SMSDK_CHECK_MEMBER_OFFSET(rend::D3D11ShaderProgram, m_pVertexShader, 0x48);
SMSDK_CHECK_MEMBER_OFFSET(rend::D3D11ShaderProgram, m_shaderPath, 0x50);
SMSDK_CHECK_MEMBER_OFFSET(rend::D3D11ShaderProgram, m_vsEntry, 0x70);
SMSDK_CHECK_MEMBER_OFFSET(rend::D3D11ShaderProgram, m_psEntry, 0x90);
SMSDK_CHECK_MEMBER_OFFSET(rend::D3D11ShaderProgram, m_mapPixelShaderBindings, 0xB0);
SMSDK_CHECK_MEMBER_OFFSET(rend::D3D11ShaderProgram, m_mapVertexShaderBindings, 0xF0);
SMSDK_CHECK_MEMBER_OFFSET(rend::D3D11ShaderProgram, m_uInputDescHash, 0x130);
SMSDK_CHECK_MEMBER_OFFSET(rend::D3D11ShaderProgram, m_vecDefines, 0x138);
SMSDK_CHECK_STRUCT_SIZE(rend::D3D11ShaderProgram, 0x150);



class D3D11Layout : public rend::D3D11Resource
{
	/* 0x0028 */ SDK_MEM_PUB ID3D11InputLayout* m_pDxLayout;
}; // Size: 0x30

SMSDK_CHECK_MEMBER_OFFSET(rend::D3D11Layout, m_pDxLayout, 0x28);
SMSDK_CHECK_STRUCT_SIZE(rend::D3D11Layout, 0x30);
}

SMSDK_END_NAMESPACE