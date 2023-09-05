#include "AvalonPch.h"
#include "Entity.h"

namespace Avalon
{
	void Entity::Render() const
	{
		for (Component* rc : mComponents)
		{
			rc->Render();
		}
	}

	void Entity::AddComponent(Component* component)
	{
		component->SetOwner(this);
		mComponents.push_back(component);
	}
}