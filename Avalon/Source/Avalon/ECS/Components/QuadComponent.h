#pragma once
#include "Avalon/ECS/Components/Component.h"

namespace Avalon
{
	class QuadComponent : public Component
	{
	public:
		QuadComponent(Entity* const owner = nullptr, Vec2 size = Vec2(1), Vec4 color = Vec4(1)) : Component(owner), size(size), color(color) {}
		virtual ~QuadComponent() = default;

		void Initialize() override;
		void Update(float deltaTime) override {}
		void Render(float deltaTime) override;

		void Serialize(YAML::Emitter& out) override;
		void Deserialize(YAML::Node quadComponentNode) override;

	protected:
		Vec2 size;
		Vec4 color;
	};
}

