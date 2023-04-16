#pragma once
#include "Avalon/Log/Log.h"

#ifndef AVALON_PLATFORM_WINDOWS
	#error Avalon only supports Windows
#endif

#ifdef AVALON_DEBUG
	#define AVALON_ENABLE_ASSERTS
#endif

#ifdef AVALON_ENABLE_ASSERTS
	//#define AVALON_ASSERT(x, ...) { if(!x) { AVALON_LOG_ERROR("Assertion failed: {0}", __VA_ARGS__); __debugbreak(); } } // Uncomment when developing app
	#define AVALON_CORE_ASSERT(x, ...) { if(!x) { AVALON_CORE_ERROR("Assertion failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define AVALON_ASSERT(x, ...)
	#define AVALON_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)
