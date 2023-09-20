#pragma once
#include "Avalon/ECS/Components/Component.h"

namespace Avalon
{
	class Entity;

	class TransformComponent : public Component
	{
	public:
		Vec3 position;
		Vec2 rotation;
		Vec2 scale;

	public:
		TransformComponent(Entity* const owner = nullptr, Vec3 position = Vec3(0.f), Vec2 rotaiton = Vec2(0.f), Vec2 scale = Vec2(1.f)) :
			Component(owner), position(position), rotation(rotation), scale(scale) 
		{}
		virtual ~TransformComponent() = default;

		void Initialize() override;
		void Update(float deltaTime) override;
		void Render(float deltaTime) override;
		void Serialize(YAML::Emitter& out) override;
	};
}

