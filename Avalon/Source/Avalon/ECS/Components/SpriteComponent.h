#pragma once

#include "Avalon/ECS/Components/Component.h"

namespace Avalon
{
	class Entity;

	class SpriteComponent : public Component
	{
	public:
		SpriteComponent(Entity* const owner = nullptr, std::string texturePath = "Assets/Textures/Fish.png", Vec4 tintColor = Vec4(1.f)) : 
			Component(owner), texturePath(texturePath), tintColor(tintColor) 
		{}
		virtual ~SpriteComponent() = default;

		void Initialize() override;
		void Update(float deltaTime) override;
		void Render(float deltaTime) override;

		void Serialize(YAML::Emitter& out) override;
		void Deserialize(YAML::Node spriteComponentNode) override;

	protected:
		std::shared_ptr<Texture2D> texture2D = nullptr;
		std::string texturePath;
		Vec4 tintColor;
	};
}

