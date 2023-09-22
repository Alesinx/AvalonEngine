#include "AvalonPch.h"
#include "Scene.h"
#include "Avalon/ECS/Components/Component.h"
#include "Avalon/ECS/Components/SpriteComponent.h"
#include "Avalon/ECS/Components/VerticalMovementComponent.h"
#include "Avalon/ECS/Components/QuadComponent.h"

#include <yaml-cpp/yaml.h>

namespace YAML {

	template<>
	struct convert<glm::vec2>
	{
		static Node encode(const glm::vec2& rhs)
		{
			Node node;
			node.push_back(rhs.x);
			node.push_back(rhs.y);
			return node;
		}

		static bool decode(const Node& node, glm::vec2& rhs)
		{
			if (!node.IsSequence() || node.size() != 2)
				return false;

			rhs.x = node[0].as<float>();
			rhs.y = node[1].as<float>();
			return true;
		}
	};

	template<>
	struct convert<glm::vec3>
	{
		static Node encode(const glm::vec3& rhs)
		{
			Node node;
			node.push_back(rhs.x);
			node.push_back(rhs.y);
			node.push_back(rhs.z);
			return node;
		}

		static bool decode(const Node& node, glm::vec3& rhs)
		{
			if (!node.IsSequence() || node.size() != 3)
				return false;

			rhs.x = node[0].as<float>();
			rhs.y = node[1].as<float>();
			rhs.z = node[2].as<float>();
			return true;
		}
	};

	template<>
	struct convert<glm::vec4>
	{
		static Node encode(const glm::vec4& rhs)
		{
			Node node;
			node.push_back(rhs.x);
			node.push_back(rhs.y);
			node.push_back(rhs.z);
			node.push_back(rhs.w);
			return node;
		}

		static bool decode(const Node& node, glm::vec4& rhs)
		{
			if (!node.IsSequence() || node.size() != 4)
				return false;

			rhs.x = node[0].as<float>();
			rhs.y = node[1].as<float>();
			rhs.z = node[2].as<float>();
			rhs.w = node[3].as<float>();
			return true;
		}
	};
}

namespace Avalon
{
	void Scene::Initialize()
	{
		for (const auto& entity : entities)
		{
			entity->Initialize();
		}
	}

	void Scene::Update(float deltaTime)
	{
		for (const auto& entity : entities)
		{
			entity->Update(deltaTime);
		}
	}

	void Scene::Render(float deltaTime)
	{
		for (const auto& entity : entities)
		{
			entity->Render(deltaTime);
		}
	}

	void Scene::Serialize(const std::string& filepath)
	{
        YAML::Emitter out;
        out << YAML::BeginMap;
        out << YAML::Key << "Scene";
        out << YAML::Value << YAML::BeginMap;

        out << YAML::Key << "Name";
        out << YAML::Value << name;

        out << YAML::Key << "Entities";
        out << YAML::Value << YAML::BeginSeq;

		for (const auto& entity : entities)
		{
			entity->Serialize(out);
		}

        out << YAML::EndSeq;
        out << YAML::EndMap;

		std::ofstream fout(filepath);
		fout << out.c_str();
	}

	bool Scene::Deserialize(const std::string filePath)
	{
		std::ifstream stream(filePath);
		std::stringstream strStream;
		strStream << stream.rdbuf();

		YAML::Node data = YAML::Load(strStream.str());
		if (!data["Scene"])
			return false;

		YAML::Node sceneNode = data["Scene"];
		std::string sceneName = sceneNode["Name"].as<std::string>();
		AVALON_CORE_TRACE("Deserializing scene '{0}'", sceneName);
		this->name = sceneName;

		YAML::Node entitiesNode = sceneNode["Entities"];
		if (entitiesNode)
		{
			for (YAML::Node entityNodeIterator : entitiesNode)
			{
				YAML::Node entityNode = entityNodeIterator["Entity"];

				// Move into Entity::Deserialize() or Entity(YAML::Node entityNode)
;				uint64_t id = entityNode["id"].as<uint64_t>();
				std::string name = entityNode["name"].as<std::string>();

				AVALON_CORE_TRACE("Deserializing entity: ID = {0}, name = {1}", id, name);

				std::unique_ptr<Entity>& entity = entities.emplace_back(new Entity(id, name));

				YAML::Node componentsNode = entityNode["Components"];
				if (componentsNode)
				{
					for (YAML::Node componentNodeIterator : componentsNode)
					{
						if (componentNodeIterator["TransformComponent"])
						{
							// Move into TransformComponent::Deserialize() or TransformComponent(YAML::Node transformComponentNode)
							YAML::Node transformComponentNode = componentNodeIterator["TransformComponent"];
							Vec3 position = transformComponentNode["position"].as<glm::vec3>();
							Vec2 rotation = transformComponentNode["rotation"].as<glm::vec2>();
							Vec2 scale = transformComponentNode["scale"].as<glm::vec2>();
							entity->SetTransform(position, rotation, scale);
						}
						else if (componentNodeIterator["SpriteComponent"])
						{
							YAML::Node spriteComponentNode = componentNodeIterator["SpriteComponent"];
							std::string texturePath = spriteComponentNode["texturePath"].as<std::string>();
							Vec4 tintColor = spriteComponentNode["tintColor"].as<glm::vec4>();
							entity->CreateComponent<SpriteComponent>(texturePath, tintColor);
						}
						else if (componentNodeIterator["QuadComponent"])
						{
							YAML::Node quadComponent = componentNodeIterator["QuadComponent"];
							Vec2 size = quadComponent["size"].as<glm::vec2>();
							Vec4 color = quadComponent["color"].as<glm::vec4>();
							entity->CreateComponent<QuadComponent>(size, color);
						}
						else if (componentNodeIterator["VerticalMovementComponent"])
						{
							YAML::Node verticalMovementComponent = componentNodeIterator["VerticalMovementComponent"];
							float movingDown = verticalMovementComponent["movingDown"].as<bool>();
							float initialOffset = verticalMovementComponent["initialOffset"].as<float>();
							float maxOffset = verticalMovementComponent["maxOffset"].as<float>();
							float speed = verticalMovementComponent["speed"].as<float>();
							entity->CreateComponent<VerticalMovementComponent>(movingDown, initialOffset, maxOffset, speed);
						}
					}
				}
			}
		}
	}

	void ExampleScene::Initialize() 
	{
		// Create entity1 first and place it in front of entity2 to test alpha threshold
		auto& entity2 = entities.emplace_back(new Entity(1, "entity1", Vec3(0.5f, 0.f, 0.5f)));
		entity2->CreateComponent<SpriteComponent>("Assets/Textures/Fish.png", Vec4(0.7f, 1.f, 1.f, 1.f));
		entity2->CreateComponent<VerticalMovementComponent>(1.f);

		auto& entity1 = entities.emplace_back(new Entity(2, "entity2"));
		entity1->CreateComponent<SpriteComponent>();
		entity1->CreateComponent<VerticalMovementComponent>(true, 0.f);

		Scene::Initialize();
	}
}