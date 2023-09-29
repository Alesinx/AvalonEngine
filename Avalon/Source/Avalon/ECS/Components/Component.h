#pragma once
#include "Avalon/Core/Core.h"
#include "Avalon/Renderer/Texture.h"

namespace YAML
{
	class Emitter;
	class Node;
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

		virtual void Initialize(){}
		virtual void Update(float deltaTime){}
		virtual void Render(float deltaTime){}
		virtual void Serialize(YAML::Emitter& out){}
		virtual void Deserialize(const YAML::Node& componentNode){}

	protected:
		Entity* mOwningEntity;
	};
}