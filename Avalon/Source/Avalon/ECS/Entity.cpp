#include "AvalonPch.h"
#include "Avalon/ECS/Entity.h"
#include "Avalon/Scene/Scene.h"

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
}