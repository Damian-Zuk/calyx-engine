// 
// Assert macros that trigger debugbreak
// From: https://github.com/TheCherno/Hazel/blob/master/Hazel/src/Hazel/Core/Assert.h
// 
#pragma once

#include "Calyx/Core/Base.h"
#include "Calyx/Debug/Logger.h"
#include <filesystem>

#ifdef CALYX_DEBUG
	#if defined(CALYX_PLATFORM_WINDOWS)
		#define CX_DEBUGBREAK() __debugbreak()
	#elif defined(CALYX_PLATFORM_LINUX)
		#include <signal.h>
		#define CX_DEBUGBREAK() raise(SIGTRAP)
	#endif
	#define CX_ENABLE_ASSERT
#else
	#define CX_DEBUGBREAK()
	#define NDEBUG
#endif

#define CX_ENABLE_VERIFY

#ifdef CX_ENABLE_ASSERT
// Alteratively we could use the same "default" message for both "WITH_MSG" and "NO_MSG" and
// provide support for custom formatting by concatenating the formatting string instead of having the format inside the default message
	#define CX_INTERNAL_ASSERT_IMPL(type, check, msg, ...) { if(!(check)) { CX##type##ERROR(msg, __VA_ARGS__); CX_DEBUGBREAK(); } }
	#define CX_INTERNAL_ASSERT_WITH_MSG(type, check, ...) CX_INTERNAL_ASSERT_IMPL(type, check, "Assertion failed: {0}", __VA_ARGS__)
	#define CX_INTERNAL_ASSERT_NO_MSG(type, check) CX_INTERNAL_ASSERT_IMPL(type, check, "Assertion '{0}' failed at {1}:{2}", CX_STRINGIFY_MACRO(check), std::filesystem::path(__FILE__).filename().string(), __LINE__)

	#define CX_INTERNAL_ASSERT_GET_MACRO_NAME(arg1, arg2, macro, ...) macro
	#define CX_INTERNAL_ASSERT_GET_MACRO(...) CX_EXPAND_MACRO( CX_INTERNAL_ASSERT_GET_MACRO_NAME(__VA_ARGS__, CX_INTERNAL_ASSERT_WITH_MSG, CX_INTERNAL_ASSERT_NO_MSG) )

	// Currently accepts at least the condition and one additional parameter (the message) being optional
	#define CX_ASSERT(...) CX_EXPAND_MACRO( CX_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_, __VA_ARGS__) )
	#define CX_CORE_ASSERT(...) CX_EXPAND_MACRO( CX_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_CORE_, __VA_ARGS__) )
#else
	#define CX_ASSERT(...)
	#define CX_CORE_ASSERT(...)
#endif

#ifdef CX_ENABLE_VERIFY
	// Alteratively we could use the same "default" message for both "WITH_MSG" and "NO_MSG" and
	// provide support for custom formatting by concatenating the formatting string instead of having the format inside the default message
	#define CX_INTERNAL_VERIFY_IMPL(type, check, msg, ...) { if(!(check)) { CX##type##ERROR(msg, __VA_ARGS__); CX_DEBUGBREAK(); } }
	#define CX_INTERNAL_VERIFY_WITH_MSG(type, check, ...) CX_INTERNAL_VERIFY_IMPL(type, check, "Verify failed: {0}", __VA_ARGS__)
	#define CX_INTERNAL_VERIFY_NO_MSG(type, check) CX_INTERNAL_VERIFY_IMPL(type, check, "Verify '{0}' failed at {1}:{2}", CX_STRINGIFY_MACRO(check), std::filesystem::path(__FILE__).filename().string(), __LINE__)

	#define CX_INTERNAL_VERIFY_GET_MACRO_NAME(arg1, arg2, macro, ...) macro
	#define CX_INTERNAL_VERIFY_GET_MACRO(...) CX_EXPAND_MACRO( CX_INTERNAL_VERIFY_GET_MACRO_NAME(__VA_ARGS__, CX_INTERNAL_VERIFY_WITH_MSG, CX_INTERNAL_VERIFY_NO_MSG) )

	// Currently accepts at least the condition and one additional parameter (the message) being optional
	#define CX_VERIFY(...) CX_EXPAND_MACRO( CX_INTERNAL_VERIFY_GET_MACRO(__VA_ARGS__)(_, __VA_ARGS__) )
	#define CX_CORE_VERIFY(...) CX_EXPAND_MACRO( CX_INTERNAL_VERIFY_GET_MACRO(__VA_ARGS__)(_CORE_, __VA_ARGS__) )
#else
	#define CX_VERIFY(...)
	#define CX_CORE_VERIFY(...)
#endif

#define CX_THROW_ERROR(...) \
	CX_CORE_ERROR(__VA_ARGS__); //CX_CORE_ASSERT(false);
