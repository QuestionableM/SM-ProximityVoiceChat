#pragma once

#include "SmSdk/Gui/GuiBase.hpp"
#include "SmSdk/config.hpp"

#include <deque>

SMSDK_BEGIN_NAMESPACE

struct ChatMessage
{
    SMSDK_API ChatMessage(const std::string_view& author, const std::string_view& message);

	/* 0x0000 */ SDK_PUB std::uint64_t m_timeStamp;
	/* 0x0008 */ SDK_PUB std::string m_author;
	/* 0x0028 */ SDK_PUB std::string m_message;
}; // Size: 0x48

static_assert(offsetof(ChatMessage, ChatMessage::m_timeStamp) == 0x0, "ChatMessage::m_timeStamp: Incorrect offset");
static_assert(offsetof(ChatMessage, ChatMessage::m_author) == 0x8, "ChatMessage::m_author: Incorrect offset");
static_assert(offsetof(ChatMessage, ChatMessage::m_message) == 0x28, "ChatMessage::m_message: Incorrect offset");

static_assert(sizeof(ChatMessage) == 0x48, "ChatMessage: Incorrect Size");



class ChatGui : public GuiBase
{
    SDK_PUB SMSDK_API void postMessage(const std::string_view& message, const std::string_view& author = "");

	/* 0x0018 */ SDK_PUB MyGUI::Widget* m_pInputBackgroundWidget;
	/* 0x0020 */ SDK_PUB MyGUI::Widget* m_pBackgroundWidget;
	/* 0x0028 */ SDK_PUB MyGUI::Widget* m_pMessageWidget;
	/* 0x0030 */ SDK_PUB MyGUI::EditBox* m_pReceivedMessagesWidget;
	/* 0x0038 */ SDK_PUB std::string m_clientChatName;
	/* 0x0058 */ SDK_PUB bool m_bOpen;
    /* 0x0059 */ SDK_PRI char pad_0x59[0x3];
	/* 0x005C */ SDK_PUB float m_fTextFadeOutTimer;
	/* 0x0060 */ SDK_PRI char pad_0x60[0x4];
	/* 0x0064 */ SDK_PUB float m_fInputBackgroundOpacity;
	/* 0x0068 */ SDK_PUB float m_fTextBoxOpacity;
	/* 0x006C */ SDK_PUB float m_fTextFadeOutDelay;
	/* 0x0070 */ SDK_PUB float m_fFadeOutLength;
	/* 0x0074 */ SDK_PUB float m_fFadeInLength;
	/* 0x0078 */ SDK_PRI char pad_0x78[0x8];
	/* 0x0080 */ SDK_PUB std::deque<ChatMessage> m_postedChatMessages;
	/* 0x00A8 */ std::deque<ChatMessage> m_chatMessageQueue;
	/* 0x00D0 */ char pad_0xD0[0x20];
}; // Size: 0xF0

static_assert(offsetof(ChatGui, ChatGui::m_pInputBackgroundWidget) == 0x18, "ChatGui::m_pInputBackgroundWidget: Incorrect offset");
static_assert(offsetof(ChatGui, ChatGui::m_pBackgroundWidget) == 0x20, "ChatGui::m_pBackgroundWidget: Incorrect offset");
static_assert(offsetof(ChatGui, ChatGui::m_pMessageWidget) == 0x28, "ChatGui::m_pMessageWidget: Incorrect offset");
static_assert(offsetof(ChatGui, ChatGui::m_pReceivedMessagesWidget) == 0x30, "ChatGui::m_pReceivedMessagesWidget: Incorrect offset");
static_assert(offsetof(ChatGui, ChatGui::m_clientChatName) == 0x38, "ChatGui::m_clientChatName: Incorrect offset");
static_assert(offsetof(ChatGui, ChatGui::m_fTextFadeOutTimer) == 0x5C, "ChatGui::m_fTextFadeOutTimer: Incorrect offset");
static_assert(offsetof(ChatGui, ChatGui::m_fInputBackgroundOpacity) == 0x64, "ChatGui::m_fInputBackgroundOpacity: Incorrect offset");
static_assert(offsetof(ChatGui, ChatGui::m_fTextBoxOpacity) == 0x68, "ChatGui::m_fTextBoxOpacity: Incorrect offset");
static_assert(offsetof(ChatGui, ChatGui::m_fTextFadeOutDelay) == 0x6C, "ChatGui::m_fTextFadeOutDelay: Incorrect offset");
static_assert(offsetof(ChatGui, ChatGui::m_fFadeOutLength) == 0x70, "ChatGui::m_fFadeOutLength: Incorrect offset");
static_assert(offsetof(ChatGui, ChatGui::m_fFadeInLength) == 0x74, "ChatGui::m_fFadeInLength: Incorrect offset");
static_assert(offsetof(ChatGui, ChatGui::m_postedChatMessages) == 0x80, "ChatGui::m_postedChatMessages: Incorrect offset");
static_assert(offsetof(ChatGui, ChatGui::m_chatMessageQueue) == 0xA8, "ChatGui::m_chatMessageQueue: Incorrect offset");

static_assert(sizeof(ChatGui) == 0xF0, "ChatGui: Incorrect Size");

SMSDK_END_NAMESPACE