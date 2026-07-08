#pragma once

#include "SmSdk/Gui/GuiBase.hpp"
#include "SmSdk/config.hpp"

#include <deque>

SMSDK_BEGIN_NAMESPACE

struct ChatMessage
{
    SMSDK_API ChatMessage(const std::string_view& author, const std::string_view& message);

	/* 0x0000 */ SDK_MEM_PUB std::uint64_t m_timeStamp;
	/* 0x0008 */ SDK_MEM_PUB std::string m_author;
	/* 0x0028 */ SDK_MEM_PUB std::string m_message;
}; // Size: 0x48

SMSDK_CHECK_MEMBER_OFFSET(ChatMessage, m_timeStamp, 0x0);
SMSDK_CHECK_MEMBER_OFFSET(ChatMessage, m_author, 0x8);
SMSDK_CHECK_MEMBER_OFFSET(ChatMessage, m_message, 0x28);
SMSDK_CHECK_STRUCT_SIZE(ChatMessage, 0x48);

//
// CHAT GUI
//

class ChatGui : public GuiBase
{
    SDK_PUB SMSDK_API void postMessage(const std::string_view& message, const std::string_view& author = "");

	/* 0x0018 */ SDK_MEM_PUB MyGUI::Widget* m_pInputBackgroundWidget;
	/* 0x0020 */ SDK_MEM_PUB MyGUI::Widget* m_pBackgroundWidget;
	/* 0x0028 */ SDK_MEM_PUB MyGUI::Widget* m_pMessageWidget;
	/* 0x0030 */ SDK_MEM_PUB MyGUI::EditBox* m_pReceivedMessagesWidget;
	/* 0x0038 */ SDK_MEM_PUB std::string m_clientChatName;
	/* 0x0058 */ SDK_MEM_PUB bool m_bOpen;
    /* 0x0059 */ SDK_MEM_PRI char pad_0x59[0x3];
	/* 0x005C */ SDK_MEM_PUB float m_fTextFadeOutTimer;
	/* 0x0060 */ SDK_MEM_PRI char pad_0x60[0x4];
	/* 0x0064 */ SDK_MEM_PUB float m_fInputBackgroundOpacity;
	/* 0x0068 */ SDK_MEM_PUB float m_fTextBoxOpacity;
	/* 0x006C */ SDK_MEM_PUB float m_fTextFadeOutDelay;
	/* 0x0070 */ SDK_MEM_PUB float m_fFadeOutLength;
	/* 0x0074 */ SDK_MEM_PUB float m_fFadeInLength;
	/* 0x0078 */ SDK_MEM_PRI char pad_0x78[0x8];
	/* 0x0080 */ SDK_MEM_PUB std::deque<ChatMessage> m_postedChatMessages;
	/* 0x00A8 */ std::deque<ChatMessage> m_chatMessageQueue;
	/* 0x00D0 */ char pad_0xD0[0x20];
}; // Size: 0xF0

SMSDK_CHECK_MEMBER_OFFSET(ChatGui, m_pInputBackgroundWidget, 0x18);
SMSDK_CHECK_MEMBER_OFFSET(ChatGui, m_pBackgroundWidget, 0x20);
SMSDK_CHECK_MEMBER_OFFSET(ChatGui, m_pMessageWidget, 0x28);
SMSDK_CHECK_MEMBER_OFFSET(ChatGui, m_pReceivedMessagesWidget, 0x30);
SMSDK_CHECK_MEMBER_OFFSET(ChatGui, m_clientChatName, 0x38);
SMSDK_CHECK_MEMBER_OFFSET(ChatGui, m_fTextFadeOutTimer, 0x5C);
SMSDK_CHECK_MEMBER_OFFSET(ChatGui, m_fInputBackgroundOpacity, 0x64);
SMSDK_CHECK_MEMBER_OFFSET(ChatGui, m_fTextBoxOpacity, 0x68);
SMSDK_CHECK_MEMBER_OFFSET(ChatGui, m_fTextFadeOutDelay, 0x6C);
SMSDK_CHECK_MEMBER_OFFSET(ChatGui, m_fFadeOutLength, 0x70);
SMSDK_CHECK_MEMBER_OFFSET(ChatGui, m_fFadeInLength, 0x74);
SMSDK_CHECK_MEMBER_OFFSET(ChatGui, m_postedChatMessages, 0x80);
SMSDK_CHECK_MEMBER_OFFSET(ChatGui, m_chatMessageQueue, 0xA8);
SMSDK_CHECK_STRUCT_SIZE(ChatGui, 0xF0);

SMSDK_END_NAMESPACE