#pragma once
#include "Avalon/ECS/Entity.h"

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

		static std::shared_ptr<Scene> CreateScene(const std::string& filePath)
		{
			std::shared_ptr<Scene> newScene = std::make_shared<Scene>();
			newScene->Deserialize(filePath);
			return newScene;
		}

	protected:
		std::string name;
		std::vector<std::unique_ptr<Entity>> entities;
	};

	class ExampleScene : public Scene
	{
	public:
		void Initialize() override;
	};
}

