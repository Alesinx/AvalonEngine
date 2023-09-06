#include "AvalonPch.h"
#include "Entity.h"

namespace Avalon
{
	void Entity::Initialize()
	{
		for (Component* rc : mComponents)
		{
			rc->Initialize();
		}
	}

	void Entity::Update(float deltaTime)
	{
		for (Component* rc : mComponents)
		{
			rc->Update(deltaTime);
		}
	}

	void Entity::Render(float deltaTime) const
	{
		for (Component* rc : mComponents)
		{
			rc->Render(deltaTime);
		}
	}

	void Entity::AddComponent(Component* component)
	{
		component->SetOwner(this);
		mComponents.push_back(component);
	}
}