#pragma once
#include "Avalon/ECS/Entity.h"

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
}

