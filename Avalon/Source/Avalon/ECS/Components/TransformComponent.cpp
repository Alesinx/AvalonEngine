#include "AvalonPch.h"
#include "TransformComponent.h"

#include "Avalon/ECS/Components/CustomTypeSerializationOperators.h"

#include <yaml-cpp/yaml.h>

namespace Avalon
{
	void TransformComponent::Initialize()
	{
	}

	void TransformComponent::Update(float deltaTime)
	{
	}

	void TransformComponent::Render(float deltaTime)
	{
	}

	void TransformComponent::Serialize(YAML::Emitter& out)
	{
		out << YAML::BeginMap;

		out << YAML::Key << "TransformComponent" << YAML::Value << YAML::BeginMap;

		out << YAML::Key << "position" << YAML::Value << position;
		out << YAML::Key << "rotation" << YAML::Value << rotation;
		out << YAML::Key << "scale" << YAML::Value << scale;

		out << YAML::EndMap; // TransformComponent

		out << YAML::EndMap;
	}
}
