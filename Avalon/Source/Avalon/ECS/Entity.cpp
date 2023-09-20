#include "AvalonPch.h"
#include "Avalon/ECS/Entity.h"
#include "Avalon/Scene/Scene.h"

#include <yaml-cpp/yaml.h>

namespace Avalon
{
	void Entity::Initialize()
	{
		for (const auto& component : components)
		{
			component->Initialize();
		}
	}

	void Entity::Update(float deltaTime)
	{
		for (const auto& component : components)
		{
			component->Update(deltaTime);
		}
	}

	void Entity::Render(float deltaTime) const
	{
		for (const auto& component : components)
		{
			component->Render(deltaTime);
		}
	}

	void Entity::Serialize(YAML::Emitter& out)
	{
        out << YAML::BeginMap;

        out << YAML::Key << "Entity" << YAML::Value << YAML::BeginMap;

        out << YAML::Key << "id" << YAML::Value << id;
        out << YAML::Key << "name" << YAML::Value << name;

        out << YAML::Key << "Components" << YAML::Value << YAML::BeginSeq;

        for (const auto& component : components)
        {
            component->Serialize(out);
        }

        out << YAML::EndSeq; // Components

        out << YAML::EndMap; // Entity

        out << YAML::EndMap;
	}

	void Entity::Deserialize()
	{
	}

	void Transform::Serialize(YAML::Emitter& out)
	{

	}

	void Transform::Deserialize()
	{
	}
}