#include "AvalonPch.h"
#include "Avalon/ECS/Components/SpriteComponent.h"
#include "Avalon/ECS/Entity.h"
#include "Avalon/Renderer/Renderer2D.h"

#include "Avalon/ECS/Components/CustomTypeSerializationOperators.h"

#include <yaml-cpp/yaml.h>

namespace Avalon
{
	void SpriteComponent::Initialize()
	{
		texture2D = Avalon::Texture2D::Create(texturePath);
	}

	void SpriteComponent::Update(float deltaTime)
	{
	}

	void SpriteComponent::Render(float deltaTime)
	{
		Vec3 ownerPos = mOwningEntity->GetTransform().position;
		Vec2 ownerScale = mOwningEntity->GetTransform().scale;
		Renderer2D::DrawQuad(ownerPos, ownerScale, texture2D, tintColor);
	}

	void SpriteComponent::Serialize(YAML::Emitter& out)
	{
		out << YAML::BeginMap;

		out << YAML::Key << "SpriteComponent" << YAML::Value << YAML::BeginMap;

		out << YAML::Key << "texturePath" << YAML::Value << texturePath;
		out << YAML::Key << "tintColor" << YAML::Value << tintColor;

		out << YAML::EndMap; // SpriteComponent

		out << YAML::EndMap;
	}

	void SpriteComponent::Deserialize(const YAML::Node& spriteComponentNode)
	{
		texturePath = spriteComponentNode["texturePath"].as<std::string>();
		tintColor = spriteComponentNode["tintColor"].as<glm::vec4>();
	}
}