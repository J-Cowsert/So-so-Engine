#pragma once

#include <memory>

#ifdef SS_PLATFORM_WINDOWS
	#define SS_DEBUGBREAK() __debugbreak()
#elif defined(SS_PLATFORM_LINUX)
	#include <signal.h>
	#define SS_DEBUGBREAK() raise(SIGTRAP)
#else
#error "Platform doesn't support debugbreak yet"
#endif // SS_PLATFORM_WINDOWS

#ifdef SS_DEBUG
	#define SS_CORE_ASSERTS
#endif

#ifdef SS_CORE_ASSERTS
	#define SS_ASSERT(x, ...) { if(!(x)) { SS_ERROR("Assertion Failed: {0}", __VA_ARGS__); SS_DEBUGBREAK(); } }
	#define SS_CORE_ASSERT(x, ...) { if(!(x)) { SS_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); SS_DEBUGBREAK(); } }
#else
	#define SS_ASSERT(x, ...)
	#define SS_CORE_ASSERT(x, ...)
#endif // SS_CORE_ASSERTS

#define BIT(x) (1 << x)
#define SS_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)
