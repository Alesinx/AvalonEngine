#pragma once
#include "Avalon/ECS/Entity.h"
#include "Avalon/ECS/Component.h"

namespace Avalon
{
	class Scene
	{
	public:
		Scene() = default;
		virtual ~Scene() = default;

		virtual void Initialize();
		virtual void Update(float deltaTime);
		virtual void Render(float deltaTime);

	protected:
		std::vector<std::unique_ptr<Entity>> entities;
	};

	class ExampleScene : public Scene
	{
	public:
		void Initialize() override
		{
			auto& entity = entities.emplace_back(new Entity());
			//entity->CreateComponent<QuadComponent>();
			entity->CreateComponent<SpriteComponent>();
			entity->CreateComponent<VerticalMovementComponent>();

			Scene::Initialize();
		}
	};
}

