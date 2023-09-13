#include "AvalonPch.h"
#include "Scene.h"

void Avalon::Scene::Initialize()
{
	for (const auto& entity : entities)
	{
		entity->Initialize();
	}
}

void Avalon::Scene::Update(float deltaTime)
{
	for (const auto& entity : entities)
	{
		entity->Update(deltaTime);
	}
}

void Avalon::Scene::Render(float deltaTime)
{
	for (const auto& entity : entities)
	{
		entity->Render(deltaTime);
	}
}
