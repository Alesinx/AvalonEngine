#pragma once

#include "Avalon/ECS/Components/Component.h"

namespace Avalon
{
	class Entity;

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
}

