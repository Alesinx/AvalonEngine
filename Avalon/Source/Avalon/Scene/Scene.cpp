#include "AvalonPch.h"
#include "Scene.h"
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

	void Scene::Deserialize()
	{
		AVALON_CORE_ASSERT(true, "Scene deserialize not implemented yet");
	}
}