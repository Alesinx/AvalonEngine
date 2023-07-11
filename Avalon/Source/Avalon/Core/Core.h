#pragma once
#include "Avalon/Log/Log.h"
#include <glm/glm.hpp>

// Platform detection using predefined macros
#ifdef _WIN32
	/* Windows x64/x86 */
	#ifdef _WIN64
		/* Windows x64  */
		#define AVALON_PLATFORM_WINDOWS
	#else
		/* Windows x86 */
		#error "x86 Builds are not supported!"
	#endif
 /* We have to check __ANDROID__ before __linux__
  * since android is based on the linux kernel
  * it has __linux__ defined */
#elif defined(__ANDROID__)
	#define AVALON_PLATFORM_ANDROID
		#error "Android is not supported!"
	#elif defined(__linux__)
		#define AVALON_PLATFORM_LINUX
	#error "Linux is not supported!"
#else
	/* Unknown compiler/platform */
	#error "Unknown platform!"
#endif // End of platform detection

#ifdef AVALON_DEBUG
	#if defined(AVALON_PLATFORM_WINDOWS)
		#define AVALON_DEBUGBREAK() __debugbreak()
	#elif defined(AVALON_PLATFORM_LINUX)
		#include <signal.h>
		#define AVALON_DEBUGBREAK() raise(SIGTRAP)
	#else
		#error "Platform doesn't support debugbreak yet!"
	#endif

	#define AVALON_ENABLE_ASSERTS
#else
	#define AVALON_DEBUGBREAK()
#endif

#ifdef AVALON_ENABLE_ASSERTS
	#define AVALON_ASSERT(x, ...) { if(!(x)) { AVALON_ERROR("Assertion failed: {0}", __VA_ARGS__); AVALON_DEBUGBREAK(); } }
	#define AVALON_CORE_ASSERT(x, ...) { if(!(x)) { AVALON_CORE_ERROR("Assertion failed: {0}", __VA_ARGS__); AVALON_DEBUGBREAK(); } }
#else
	#define AVALON_ASSERT(x, ...) {x}
	#define AVALON_CORE_ASSERT(x, ...) {x}
#endif

#define BIT(x) (1 << x)

#define BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

// Math definitions
using Vec2 = glm::vec2;
using Vec3 = glm::vec3;
using Vec4 = glm::vec4;
using Mat2 = glm::mat2;
using Mat3 = glm::mat3;
using Mat4 = glm::mat4;
