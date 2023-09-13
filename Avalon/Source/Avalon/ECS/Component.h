#pragma once

#include "Avalon/Core/Core.h"
#include "Avalon/Renderer/Texture.h"

namespace Avalon
{
	class Entity;
	struct Transform;

	class Component
	{
	public:
		Component() { mOwningEntity = nullptr; }
		Component(Entity* const owner) : mOwningEntity(owner) {}
		virtual ~Component() = default;

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
		virtual ~QuadComponent() = default;

		void Initialize() override;
		void Update(float deltaTime) override;
		void Render(float deltaTime) override;

	protected:
		Vec2 size;
		Vec4 color;
	};

	class SpriteComponent : public Component
	{
	public:
		SpriteComponent(Entity* const owner = nullptr) : Component(owner) {}
		virtual ~SpriteComponent() = default;

		void Initialize() override;
		void Update(float deltaTime) override;
		void Render(float deltaTime) override;

	protected:
		std::shared_ptr<Texture2D> texture2D = nullptr;
	};

	class VerticalMovementComponent : public Component
	{
	public:
		VerticalMovementComponent(Entity* const owner = nullptr, int maxOffset = 1.f, float speed = 1.f) : Component(owner), maxOffset(maxOffset), speed(speed) {}
		virtual ~VerticalMovementComponent() = default;

		void Initialize() override;
		void Update(float deltaTime) override;
		void Render(float deltaTime) override;

	public:
		float maxOffset = 1.f;
		float speed = 1.f;
	private:
		int direction = 1;
		Vec3 originalPosition = { 0.f, 0.f, 0.f };
	};
}