#pragma once
#include "Avalon/ECS/Entity.h"

// delete
#include "Avalon/Time/Time.h"
#include "Avalon/ECS/Components/SpriteComponent.h"
#include "Avalon/ECS/Components/VerticalMovementComponent.h"

namespace YAML
{
	class Node;
}

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
		virtual bool Deserialize(const std::string filePath);

		virtual std::unique_ptr<Entity>& CreateAndAddEntity(YAML::Node entityNode);

	protected:
		std::string name;
		std::vector<std::unique_ptr<Entity>> entities;
	};

	class BenchmarkScene : public Scene
	{
		void Initialize() override 
		{
			entities.reserve(100 * 10);

			float paddingX = 1;
			float paddingY = 1;

			for (int i = 0; i < 100; i++)
			{
				for (int j = 0; j < 10; j++)
				{
					float time = Time::GetCurrentTime();
					AVALON_CORE_TRACE("==========================================================================================");
					AVALON_CORE_TRACE("Creating entity!"); time = Time::GetCurrentTime();
					Vec3 position = Vec3(i * paddingX, j * paddingY, 0.f);
					std::unique_ptr<Entity>& entity = entities.emplace_back(std::make_unique<Entity>(this, 1, "a", position));
					AVALON_CORE_TRACE("Entity created. Time elapsed {0}", Time::GetCurrentTime() - time);
					AVALON_CORE_TRACE("Creating and attaching SpriteComponent"); time = Time::GetCurrentTime();
					entity->CreateComponent<SpriteComponent>();
					AVALON_CORE_TRACE("SpriteComponent created. Time elapsed {0}", Time::GetCurrentTime() - time);
					AVALON_CORE_TRACE("Creating and attaching VerticalMovementComponent"); time = Time::GetCurrentTime();
					entity->CreateComponent<VerticalMovementComponent>();
					AVALON_CORE_TRACE("VerticalMovementComponent created. Time elapsed {0}", Time::GetCurrentTime() - time);
					AVALON_CORE_TRACE("Total number of entities: {0}", entities.size());

					Scene::Initialize();
				}
			}
		}
	};
}
