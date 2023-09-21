#pragma once

#include "Avalon/ECS/Components/Component.h"

namespace Avalon
{
	class VerticalMovementComponent : public Component
	{
	public:
		VerticalMovementComponent(Entity* const owner = nullptr, bool movingDown = true, float initialOffset = 0.f, float maxOffset = 1.f, float speed = 1.f) :
			Component(owner), direction(movingDown? 1 : -1), initialOffset(initialOffset), currentOffset(initialOffset), maxOffset(maxOffset), speed(speed) {}
		virtual ~VerticalMovementComponent() = default;

		void Initialize() override;
		void Update(float deltaTime) override;
		void Render(float deltaTime) {}
		void Serialize(YAML::Emitter& out) override;

	protected:
		float initialOffset;
		float maxOffset = 1.f;
		float speed = 1.f;
		int direction = 1;

		float currentOffset;
		Vec3 originalPosition = { 0.f, 0.f, 0.f };
	};
}
