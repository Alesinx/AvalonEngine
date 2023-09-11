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

		virtual void Initialize() {}
		virtual void Update(float deltaTime) {}
		virtual void Render(float deltaTime) {}

	};

	class ExampleScene : public Scene
	{
	public:
		void Initialize() override
		{

			entity1 = std::unique_ptr<Entity>(new Entity());
			entity1->CreateComponent<QuadComponent>(Vec3(0.1f));
			entity1->CreateComponent<QuadComponent>(Vec3(1.f), Vec4(0.8f));
			entity1->CreateComponent<VerticalMovementComponent>();
			entity1->Initialize();
		}

		void Update(float deltaTime) override
		{
			entity1->Update(deltaTime);
		}

		void Render(float deltaTime) override
		{
			entity1->Render(deltaTime);
		}

	private:
		std::unique_ptr<Avalon::Entity> entity1;
	};
}

