#pragma once
#include "Avalon/Log/Log.h"
#include <glm/glm.hpp>

#ifndef AVALON_PLATFORM_WINDOWS
	#error Avalon only supports Windows
#endif

#ifdef AVALON_DEBUG
	#define AVALON_ENABLE_ASSERTS
#endif

#ifdef AVALON_ENABLE_ASSERTS
	#define AVALON_ASSERT(x, ...) { if(!(x)) { AVALON_ERROR("Assertion failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define AVALON_CORE_ASSERT(x, ...) { if(!(x)) { AVALON_CORE_ERROR("Assertion failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define AVALON_ASSERT(x, ...)
	#define AVALON_CORE_ASSERT(x, ...)
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
