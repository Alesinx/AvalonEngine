#pragma once

#include <glm/glm.hpp>
#include <yaml-cpp/yaml.h>

namespace Avalon
{
	YAML::Emitter& operator<<(YAML::Emitter& out, const glm::vec2& v);
	YAML::Emitter& operator<<(YAML::Emitter& out, const glm::vec3& v);
	YAML::Emitter& operator<<(YAML::Emitter& out, const glm::vec4& v);
}