#pragma once

#include "Avalon/Core/Core.h"
#include "Avalon/Renderer/Texture.h"

namespace YAML
{
	class Emitter;
}

namespace Avalon
{
	class Entity;

	class Component
	{
	public:
		Component(Entity* const owner = nullptr) : mOwningEntity(owner) {}
		virtual ~Component() = default;

		virtual void SetOwner(Entity* const owner) { mOwningEntity = owner; }

		virtual void Initialize() = 0;
		virtual void Update(float deltaTime) = 0;
		virtual void Render(float deltaTime) = 0;
		virtual void Serialize(YAML::Emitter& out) = 0;

	protected:
		Entity* mOwningEntity;
	};
}