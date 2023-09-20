#pragma once
#include "Avalon/ECS/Entity.h"
#include "Avalon/ECS/Components/Component.h"
#include "Avalon/ECS/Components/SpriteComponent.h"

namespace Avalon
{
	class Scene
	{
	public:
		Scene(const std::string& name = "Untitled scene") : name(name) {}
		virtual ~Scene() = default;

		virtual void Initialize();
		virtual void Update(float deltaTime);
		virtual void Render(float deltaTime);
		virtual void Serialize(const std::string& path);
		virtual void Deserialize();

	protected:
		std::string name;
		std::vector<std::unique_ptr<Entity>> entities;
	};

	class ExampleScene : public Scene
	{
	public:
		void Initialize() override
		{
			// Creating entity2 (and therefore rendered) before entity1 but placed in front to test alpha testing
			auto& entity2 = entities.emplace_back(new Entity("entity2", Vec3(0.5f, 0.f, 0.5f)));
			entity2->CreateComponent<SpriteComponent>("Assets/Textures/Fish.png", Vec4(0.7f, 1.f, 1.f, 1.f));
			entity2->CreateComponent<VerticalMovementComponent>(1.f);

			auto& entity1 = entities.emplace_back(new Entity("entity1"));
			entity1->CreateComponent<SpriteComponent>();
			entity1->CreateComponent<VerticalMovementComponent>(0.f);

			Scene::Initialize();
		}
	};
}

