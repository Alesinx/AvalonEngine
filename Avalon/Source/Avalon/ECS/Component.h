#pragma once

#include "Avalon/Core/Core.h"

namespace Avalon
{
	class Entity;

	class Component
	{
	public:
		Component() { mOwningEntity = nullptr; }
		Component(Entity* const owner) : mOwningEntity(owner) {}
		virtual ~Component() {}

		virtual void SetOwner(Entity* const owner) { mOwningEntity = owner; }
		virtual void Render() = 0;

	protected:
		Entity* mOwningEntity;
	};

		class QuadComponent : public Component
	{
	public:
		QuadComponent(Entity* const owner = nullptr, Vec2 size = Vec2(1), Vec4 color = Vec4(1)) : Component(owner), size(size), color(color) {}
		virtual ~QuadComponent() {}

		virtual void Render() override;

	public:
		Vec2 size;
		Vec4 color;
	};
}