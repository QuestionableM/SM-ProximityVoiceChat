#pragma once

#include "SmSdk/Util/Hashing.hpp"
#include "SmSdk/config.hpp"

#include <unordered_map>
#include <string>

SMSDK_BEGIN_NAMESPACE

class DirectoryManager
{
	SINGLETON_CLASS(DirectoryManager);

	SDK_PUB SMSDK_API static DirectoryManager* GetInstance();

	SDK_PUB SMSDK_API bool getReplacement(const std::string_view& key, std::string_view& replacement);
	SDK_PUB SMSDK_API bool replacePathR(std::string& path);

	SDK_PUB SMSDK_API static bool GetReplacement(const std::string_view& key, std::string_view& replacement);
	SDK_PUB SMSDK_API static bool ReplacePathR(std::string& path);

	/* 0x0000 */ SDK_PRI char pad_0x0[8];
	/* 0x0008 */ SDK_PUB std::unordered_map<std::string, std::string, Hashing::StringHash, std::equal_to<>> m_mapContentKeyToPathList;
}; // Size: 0x48

static_assert(offsetof(DirectoryManager, DirectoryManager::m_mapContentKeyToPathList) == 0x8, "DirectoryManager::m_pathReplacements: Incorrect offset");

static_assert(sizeof(DirectoryManager) == 0x48, "DirectoryManager: Incorrect Size");

SMSDK_END_NAMESPACE