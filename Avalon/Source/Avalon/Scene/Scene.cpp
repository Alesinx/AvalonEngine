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
}