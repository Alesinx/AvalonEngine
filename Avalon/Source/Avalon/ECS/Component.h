#pragma once

#include "Avalon/Core/Core.h"

namespace Avalon
{
	class Entity;
	struct Transform;

	class Component
	{
	public:
		Component() { mOwningEntity = nullptr; }
		Component(Entity* const owner) : mOwningEntity(owner) {}
		virtual ~Component() {}

		virtual void SetOwner(Entity* const owner) { mOwningEntity = owner; }

		virtual void Initialize() = 0;
		virtual void Update(float deltaTime) = 0;
		virtual void Render(float deltaTime) = 0;

	protected:
		Entity* mOwningEntity;
	};

	class QuadComponent : public Component
	{
	public:
		QuadComponent(Entity* const owner = nullptr, Vec2 size = Vec2(1), Vec4 color = Vec4(1)) : Component(owner), size(size), color(color) {}
		virtual ~QuadComponent() {}

		virtual void Initialize() override;
		virtual void Update(float deltaTime) override;
		virtual void Render(float deltaTime) override;

	public:
		Vec2 size;
		Vec4 color;
	};

	class VerticalMovementComponent : public Component
	{
	public:
		VerticalMovementComponent(Entity* const owner = nullptr, int maxOffset = 1, float speed = 1.f) : Component(owner), maxOffset(maxOffset), speed(speed) {}
		virtual ~VerticalMovementComponent() {}

		virtual void Initialize();
		virtual void Update(float deltaTime) override;
		virtual void Render(float deltaTime) override {}

	public:
		int maxOffset;
		float speed;
	private:
		int direction = 1;
		Vec3 originalPosition;
	};
}