#pragma once

#include <windows.h>

#include <unordered_set>
#include <functional>
#include <fstream>
#include <sstream>
#include <string>
#include <mutex>

#include "SmSdk/config.hpp"

SMSDK_BEGIN_NAMESPACE

namespace UTILS
{
class Contraption;

enum ConsoleLogType : std::uint32_t
{
	ConsoleLogType_Default = 0x1,
	ConsoleLogType_Profile = 0x2,
	ConsoleLogType_Resource = 0x4,
	ConsoleLogType_Shader = 0x8,
	ConsoleLogType_Buffer = 0x10,
	ConsoleLogType_Render = 0x20,
	ConsoleLogType_Network = 0x40,
	ConsoleLogType_System = 0x80,
	ConsoleLogType_Terrain = 0x100,
	ConsoleLogType_World = 0x200,
	ConsoleLogType_Audio = 0x400,
	ConsoleLogType_Lua = 0x800,
	ConsoleLogType_Print = 0x1000,
	ConsoleLogType_UGC = 0x2000,
	ConsoleLogType_Steam = 0x4000,
	ConsoleLogType_Warning = 0x40000000,
	ConsoleLogType_Error = 0x80000000,
};

class Console
{
	SDK_PUB SMSDK_API static Console* GetInstance();
	
	SDK_PUB virtual ~Console();
	SDK_PUB virtual void log(const std::string& msg, const WORD wColor, const ConsoleLogType eType);
	SDK_PUB virtual bool logNoRepeat(const std::string& msg, const WORD wColor, const ConsoleLogType eType);

	SDK_PRI template <typename CurArg>
	inline void variadicInternal(std::stringstream& ss, const CurArg& curArg)
	{
		ss << curArg;
	}

	SDK_PRI template <typename CurArg, typename... Args>
	inline void variadicInternal(std::stringstream& ss, const CurArg& curArg, const Args&... argList)
	{
		this->variadicInternal(ss, curArg);
		this->variadicInternal(ss, argList...);
	}

	SDK_PUB template <typename... Args>
	inline void logVariadic(WORD wColor, ConsoleLogType eType, const Args&... args)
	{
		std::stringstream ss;
		this->variadicInternal(ss, args...);

		this->log(ss.str(), wColor, eType);
	}

	SDK_PUB template <typename... Args>
	inline void logVariadicNoRepeat(WORD wColor, ConsoleLogType eType, const Args&... args)
	{
		std::stringstream ss;
		this->variadicInternal(ss, args...);

		this->logNoRepeat(ss.rdbuf()->str(), wColor, eType);
	}

	/* 0x0008 */ SDK_MEM_PRI std::function<void(const char*, unsigned int)> m_unknownFunction;
	/* 0x0048 */ SDK_MEM_PUB std::uint32_t m_uConsoleOutMask;
	/* 0x004C */ SDK_MEM_PUB std::uint32_t m_uFileOutputMask;
	/* 0x0050 */ SDK_MEM_PUB std::uint32_t m_uCallbackOutputMask;
	/* 0x0054 */ SDK_MEM_PRI char pad_0x54[0x4];
	/* 0x0058 */ SDK_MEM_PUB HANDLE m_hConsole;
	/* 0x0060 */ SDK_MEM_PUB std::ofstream m_outStream;
	/* 0x0168 */ SDK_MEM_PRI char pad_0x168[0x10];
	/* 0x0178 */ SDK_MEM_PUB bool m_bCodePageSet;
	/* 0x0179 */ SDK_MEM_PUB bool m_bConsoleAllocated;
	/* 0x017A */ SDK_MEM_PRI char pad_0x17A[0x2];
	/* 0x017C */ SDK_MEM_PUB std::uint32_t m_uWarningCounter;
	/* 0x0180 */ SDK_MEM_PUB std::uint32_t m_uErrorCounter;
	/* 0x0184 */ SDK_MEM_PRI char pad_0x184[0x4];
};
}

#define LOG_ERROR(...) UTILS::Console::GetInstance()->logVariadic(FOREGROUND_RED | FOREGROUND_INTENSITY, UTILS::ConsoleLogType_Error, __VA_ARGS__)
#define LOG_WARNING(...) UTILS::Console::GetInstance()->logVariadic(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY, UTILS::ConsoleLogType_Warning, __VA_ARGS__)

SMSDK_END_NAMESPACE