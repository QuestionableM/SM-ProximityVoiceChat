#pragma once

// Additional libraries that can be added to expand the functionality of SMSDK

//#define SMSDK_ENABLE_PHYSICS
//#define SMSDK_ENABLE_JSONCPP
//#define SMSDK_ENABLE_FMOD
//#define SMSDK_ENABLE_STEAMAPI
//#define SMSDK_ENABLE_MYGUI
//#define SMSDK_ENABLE_D3D11

// WARNING: All the map getters will be wrong without the Boost uuid library
// TODO: This could be fixed by implementing the hash function that Boost uses internally for our stub
//#define SMSDK_ENABLE_BOOST

// You can optionally wrap everything into a namespace
#define SMSDK_NAMESPACE SM

#if defined(SMSDK_BUILD_DLL)
# define SMSDK_API __declspec(dllexport)
#elif defined(SMSDK_IMPORT_DLL)
# define SMSDK_API __declspec(dllimport)
#else // Static linking is the default
# define SMSDK_API
#endif

#if defined(SMSDK_IMPORT_DLL)
# define SMSDK_HIDE_RAW_STRUCT_MEMBERS
#endif

// SDK_MEM_* are used for structure/class variables so they can be easily disabled

#if defined(SMSDK_HIDE_RAW_STRUCT_MEMBERS)
# define SMSDK_CHECK_MEMBER_OFFSET(...)
# define SMSDK_CHECK_STRUCT_SIZE(...)
# define SDK_MEM_PUB private:
# define SDK_MEM_PRI private:
# define SDK_MEM_PRO private:
#else
# define SMSDK_CHECK_MEMBER_OFFSET(class, member, offset) static_assert(offsetof(class, class::member) == offset, #class "::" #member ": Incorrect offset")
# define SMSDK_CHECK_STRUCT_SIZE(class, size) static_assert(sizeof(class) == size, #class ": Incorrect Size")
# define SDK_MEM_PUB public:
# define SDK_MEM_PRI private:
# define SDK_MEM_PRO protected:
#endif

// Used for functions within structures/classes
#define SDK_PUB public:
#define SDK_PRI private:
#define SDK_PRO protected:

#include <cstdint>
#include <cstddef>

#define SINGLETON_CLASS(class_name) \
	class_name() = delete; \
	class_name(const class_name&) = delete; \
	class_name(class_name&&) = delete; \
	~class_name() = delete

#define REMOVE_COPY_CONSTRUCTORS(class_name) \
	class_name() = delete; \
	class_name(const class_name&) = delete; \
	class_name(class_name&&) = delete;

// Means that the size_t is an output of an XXH function
using XXHStringHash = size_t;

// A simple number used as a hash
struct PassthroughHash
{
	inline size_t operator()(const size_t val) const noexcept
	{
		return val;
	}
};

#ifdef SMSDK_NAMESPACE
# define SMSDK_BEGIN_NAMESPACE namespace SMSDK_NAMESPACE {
# define SMSDK_END_NAMESPACE }
# define SMSDK_USE_NAMESPACE using namespace SMSDK_NAMESPACE;
#else
# define SMSDK_BEGIN_NAMESPACE
# define SMSDK_END_NAMESPACE
# define SMSDK_USE_NAMESPACE
#endif