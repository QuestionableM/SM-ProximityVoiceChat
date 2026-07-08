#pragma once

#include "SmSdk/unreferenced_params.hpp"
#include "SmSdk/jsoncpp_include.hpp"

#include <unordered_map>
#include <functional>
#include <memory>
#include <string>
#include <deque>

SMSDK_BEGIN_NAMESPACE

class GuiBase;

struct GuiDeferredCallback
{
	/* 0x0000 */ SDK_MEM_PUB std::string m_identifier;
	/* 0x0020 */ SDK_MEM_PUB std::function<void(void)> m_callback;
}; // Size: 0x60

SMSDK_CHECK_MEMBER_OFFSET(GuiDeferredCallback, m_identifier, 0x0);
SMSDK_CHECK_MEMBER_OFFSET(GuiDeferredCallback, m_callback, 0x20);
SMSDK_CHECK_STRUCT_SIZE(GuiDeferredCallback, 0x60);

//
// GUI INTERFACE
//

class GuiInterface
{
	SDK_PUB virtual ~GuiInterface() = default;
	SDK_PUB virtual void open() {}
	SDK_PUB virtual void close() {}
	SDK_PRI virtual void func4() {}
	SDK_PRI virtual void func5(const std::string& str) { SMSDK_UNREF(str); }
	SDK_PRI virtual void func6(const std::string& str, std::int64_t a3) { SMSDK_UNREF2(str, a3); }
	SDK_PRI virtual void func7(const std::string& str, const std::string& str2) { SMSDK_UNREF2(str, str2); }
	SDK_PRI virtual void func8(const std::string& str, const std::string& str2) { SMSDK_UNREF2(str, str2); }
	SDK_PRI virtual void func9(const std::string& str, const std::string& str2, const Json::Value& json_val) { SMSDK_UNREF3(str, str2, json_val); }
	SDK_PRI virtual void func10(const std::string& str, const std::string& str2, size_t idx, const Json::Value& json_val) { SMSDK_UNREF4(str, str2, idx, json_val); }
	SDK_PRI virtual void func11() {}
	SDK_PRI virtual void func12() {}
	SDK_PUB virtual void processDeferredCallbacks() {}

	SDK_PUB SMSDK_API std::shared_ptr<GuiBase> getGuiBase();

	/* 0x0008 */ SDK_MEM_PUB std::shared_ptr<GuiBase> m_pGuiBase;
	/* 0x0018 */ SDK_MEM_PRI bool m_bSomeBool;
	/* 0x0019 */ SDK_MEM_PRI char pad_0x19[0x7];
	/* 0x0020 */ SDK_MEM_PUB std::function<void(void)> m_closeCallback;
	/* 0x0060 */ SDK_MEM_PUB std::unordered_map<std::string, std::function<void(void)>> m_mapEmptyFunctionCallbacks;
	/* 0x00A0 */ SDK_MEM_PUB std::unordered_map<std::string, std::function<void(std::int64_t)>> m_mapOneArgFunctionCallbacks;
	/* 0x00E0 */ SDK_MEM_PUB std::unordered_map<std::string, std::function<void(const std::string&)>> m_mapStringToFunction;
	/* 0x0120 */ SDK_MEM_PRI char pad_0x120[0x80];
	/* 0x01A0 */ SDK_MEM_PUB std::unordered_map<std::string, std::unordered_map<std::string, std::function<void(size_t, const Json::Value&)>>> m_mapMapCallbackStorage;
	/* 0x01E0 */ SDK_MEM_PRI char pad_0x1E0[0x80];
	/* 0x0260 */ SDK_MEM_PUB std::deque<std::function<void(void)>> m_deferredCallbackDeque;
	/* 0x0288 */ SDK_MEM_PUB std::vector<GuiDeferredCallback> m_vecDeferredCallbacks;
}; // Size: 0x2A0

SMSDK_CHECK_MEMBER_OFFSET(GuiInterface, m_pGuiBase, 0x8);
SMSDK_CHECK_MEMBER_OFFSET(GuiInterface, m_closeCallback, 0x20);
SMSDK_CHECK_MEMBER_OFFSET(GuiInterface, m_mapEmptyFunctionCallbacks, 0x60);
SMSDK_CHECK_MEMBER_OFFSET(GuiInterface, m_mapOneArgFunctionCallbacks, 0xA0);
SMSDK_CHECK_MEMBER_OFFSET(GuiInterface, m_mapStringToFunction, 0xE0);
SMSDK_CHECK_MEMBER_OFFSET(GuiInterface, m_mapMapCallbackStorage, 0x1A0);
SMSDK_CHECK_MEMBER_OFFSET(GuiInterface, m_deferredCallbackDeque, 0x260);
SMSDK_CHECK_MEMBER_OFFSET(GuiInterface, m_vecDeferredCallbacks, 0x288);
SMSDK_CHECK_STRUCT_SIZE(GuiInterface, 0x2A0);

SMSDK_END_NAMESPACE