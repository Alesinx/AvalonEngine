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

	class QuadComponent : public Component
	{
	public:
		QuadComponent(Entity* const owner = nullptr, Vec2 size = Vec2(1), Vec4 color = Vec4(1)) : Component(owner), size(size), color(color) {}
		virtual ~QuadComponent() = default;

		void Initialize() override;
		void Update(float deltaTime) override {}
		void Render(float deltaTime) override;

		void Serialize(YAML::Emitter& out) override;

	protected:
		Vec2 size;
		Vec4 color;
	};

	class VerticalMovementComponent : public Component
	{
	public:
		VerticalMovementComponent(Entity* const owner = nullptr, float initialOffset = 0.f, float maxOffset = 1.f, float speed = 1.f) : 
			Component(owner), offset(initialOffset), maxOffset(maxOffset), speed(speed) {}
		virtual ~VerticalMovementComponent() = default;

		void Initialize() override;
		void Update(float deltaTime) override;
		void Render(float deltaTime) {}
		void Serialize(YAML::Emitter& out) override;

	protected:
		float offset;
		float maxOffset = 1.f;
		float speed = 1.f;
		int direction = 1;
		Vec3 originalPosition = { 0.f, 0.f, 0.f };
	};
}