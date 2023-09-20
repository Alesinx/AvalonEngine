#include "AvalonPch.h"
#include "Avalon/ECS/Components/QuadComponent.h"
#include "Avalon/ECS/Entity.h"
#include "Avalon/Renderer/Renderer2D.h"

#include <yaml-cpp/yaml.h>

namespace Avalon
{
	void QuadComponent::Initialize()
	{
	}

	void QuadComponent::Render(float deltaTime)
	{
		Vec3 ownerPos = mOwningEntity->GetTransform().position;
		Vec2 ownerScale = mOwningEntity->GetTransform().scale;
		Renderer2D::DrawQuad(ownerPos, ownerScale * size, color);
	}

	void QuadComponent::Serialize(YAML::Emitter& out)
	{
		out << YAML::BeginMap;

		out << YAML::Key << "QuadComponent" << YAML::Value << YAML::BeginMap;

		out << YAML::Key << "size" << YAML::Value << "{1.0f, 1.0f, 1.0f}";
		out << YAML::Key << "color" << YAML::Value << "{1.0f, 1.0f, 1.0f, 1.0f}";

		out << YAML::EndMap; // QuadComponent

		out << YAML::EndMap;
	}
}