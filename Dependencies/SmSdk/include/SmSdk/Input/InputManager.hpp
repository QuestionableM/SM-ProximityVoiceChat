#pragma once

#include "SmSdk/config.hpp"

#include <string>
#include <deque>

SMSDK_BEGIN_NAMESPACE

enum class EKeyState : std::uint32_t
{
	None  = 0,
	Press = 1,
	Hold  = 2
};

enum class EMouseButton : std::uint32_t
{
	Left    = 0,
	Right   = 1,
	Middle  = 2,
	Button1 = 3,
	Button2 = 4
};

enum class EInputEventType : std::uint32_t
{
	Keyboard    = 0,
	Mouse       = 1,
	MouseScroll = 2,
	MouseMove   = 3
};



struct MouseData
{
	/* 0x0000 */ SDK_MEM_PUB std::int32_t m_x;
	/* 0x0004 */ SDK_MEM_PUB std::int32_t m_y;
	/* 0x0008 */ SDK_MEM_PUB std::int32_t m_scroll;
}; // Size: 0xC

SMSDK_CHECK_STRUCT_SIZE(MouseData, 0xC);

struct InputEvent
{
	/* 0x0000 */ SDK_MEM_PUB EInputEventType m_eventType;
	/* 0x0004 */ SDK_MEM_PRI char pad_0x4[0x4];
	/* 0x0008 */ SDK_MEM_PUB std::wstring m_someName;
	/* 0x0028 */ SDK_MEM_PRI char pad_0x28[0x18];
}; // Size: 0x40

SMSDK_CHECK_STRUCT_SIZE(InputEvent, 0x40);

class InputManager
{
	REMOVE_COPY_CONSTRUCTORS(InputManager);

	SDK_PUB SMSDK_API static InputManager* GetInstance();

	SDK_PUB SMSDK_API bool isKeyPressed(const char cKey) const;
	SDK_PUB SMSDK_API bool isKeyHeld(const char cKey) const;

	SDK_PUB SMSDK_API bool isMouseButtonPressed(const EMouseButton eBtn) const;
	SDK_PUB SMSDK_API bool isMouseButtonHeld(const EMouseButton eBtn) const;

	SDK_PUB SMSDK_API static bool IsKeyPressed(const char cKey);
	SDK_PUB SMSDK_API static bool IsKeyHeld(const char cKey);

	SDK_PUB SMSDK_API static bool IsMouseButtonPressed(const EMouseButton eBtn);
	SDK_PUB SMSDK_API static bool IsMouseButtonHeld(const EMouseButton eBtn);

	SDK_PUB SMSDK_API static std::int32_t GetMouseScrollDelta();

	/* 0x0000 */ SDK_MEM_PRI char pad_0x0[0xC];
	/* 0x000C */ SDK_MEM_PUB std::int32_t m_iCharacterCode;
	/* 0x0010 */ SDK_MEM_PRI char pad_0x10[0x18];
	/* 0x0028 */ SDK_MEM_PUB struct Contraption* m_pContraption;
	/* 0x0030 */ SDK_MEM_PUB MouseData m_currentMouseData;
	/* 0x003C */ SDK_MEM_PUB MouseData m_prevMouseData;
	/* 0x0048 */ SDK_MEM_PUB MouseData m_deltaMouseData;
	/* 0x0054 */ SDK_MEM_PUB bool m_bKeyPressStates[256];
	/* 0x0154 */ SDK_MEM_PUB bool m_bPrevKeyPressStates[256];
	/* 0x0254 */ SDK_MEM_PUB EKeyState m_eKeyStates[256];
	/* 0x0654 */ SDK_MEM_PUB bool m_bMouseBtnPressStates[5];
	/* 0x0659 */ SDK_MEM_PUB bool m_bMousePrevBtnPressStates[5];
	/* 0x065E */ SDK_MEM_PRI char pad_0x65E[0x2];
	/* 0x0660 */ SDK_MEM_PUB EKeyState m_eMouseBtnStates[5];
	/* 0x0674 */ SDK_MEM_PRI char pad_0x674[0x4];
	/* 0x0678 */ SDK_MEM_PUB std::deque<InputEvent> m_deqInputQueue;
	/* 0x06A0 */ SDK_MEM_PRI char pad_0x6A0[0x4];
	/* 0x06A4 */ SDK_MEM_PUB float m_fCrashTimer;
	/* 0x06A8 */ SDK_MEM_PRI char pad_0x6A8[0x8];
}; // Size: 0x6B0

SMSDK_CHECK_STRUCT_SIZE(InputManager, 0x6B0);

SMSDK_END_NAMESPACE