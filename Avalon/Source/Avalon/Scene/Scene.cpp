#include "AvalonPch.h"
#include "Scene.h"
#include "Avalon/ECS/Components/Component.h"
#include "Avalon/ECS/Components/SpriteComponent.h"
#include "Avalon/ECS/Components/VerticalMovementComponent.h"
#include "Avalon/ECS/Components/QuadComponent.h"

#include "Avalon/ECS/Components/CustomTypeSerializationOperators.h"
#include <yaml-cpp/yaml.h>

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
				CreateAndAddEntity(entityNodeIterator["Entity"]);
			}
		}
	}

	std::unique_ptr<Entity>& Scene::CreateAndAddEntity(YAML::Node entityNode)
	{
		std::unique_ptr<Entity>& entity = entities.emplace_back(std::make_unique<Entity>(this));
		entity->Deserialize(entityNode);
		return entity;
	}
}