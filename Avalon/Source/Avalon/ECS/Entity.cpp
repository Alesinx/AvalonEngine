#include "AvalonPch.h"
#include "Avalon/ECS/Entity.h"
#include "Avalon/Scene/Scene.h"
#include "Avalon/Core/Application.h"
#include "Avalon/ECS/Components/SpriteComponent.h"
#include "Avalon/ECS/Components/VerticalMovementComponent.h"
#include "Avalon/ECS/Components/QuadComponent.h"

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

		transformComponent.Serialize(out);

        for (const auto& component : components)
        {
            component->Serialize(out);
        }

        out << YAML::EndSeq; // Components

        out << YAML::EndMap; // Entity

        out << YAML::EndMap;
	}

	bool Entity::Deserialize(YAML::Node entityNode)
	{
		if(!entityNode["id"])
		{
			AVALON_CORE_ASSERT(true, "No id field in entity!");
			return false;
		}
		this->id = entityNode["id"].as<uint64_t>();
		this->name = entityNode["name"].as<std::string>();
		AVALON_CORE_TRACE("Deserializing entity: ID = {0}, name = {1}", this->id, this->name);

		YAML::Node componentsNode = entityNode["Components"];
		if (componentsNode)
		{
			for (YAML::Node componentNodeIterator : componentsNode)
			{
				if (componentNodeIterator["TransformComponent"])
				{
					transformComponent.Deserialize(componentNodeIterator["TransformComponent"]);
				}
				else if (componentNodeIterator["SpriteComponent"])
				{
					SpriteComponent& spriteComp = this->CreateComponent<SpriteComponent>();
					spriteComp.Deserialize(componentNodeIterator["SpriteComponent"]);
				}
				else if (componentNodeIterator["QuadComponent"])
				{
					QuadComponent& quadComp = this->CreateComponent<QuadComponent>();
					quadComp.Deserialize(componentNodeIterator["QuadComponent"]);
				}
				else if (componentNodeIterator["VerticalMovementComponent"])
				{
					VerticalMovementComponent& verticalMovComp = this->CreateComponent<VerticalMovementComponent>();
					verticalMovComp.Deserialize(componentNodeIterator["VerticalMovementComponent"]);
				}
			}
		}

		return true;
	}

	std::shared_ptr<Scene> Entity::GetCurrentScene()
	{
		return Application::GetInstance().GetCurrentScene();
	}
}