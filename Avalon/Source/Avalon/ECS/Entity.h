#pragma once

#include "Avalon/ECS/Components/Component.h"
#include "Avalon/ECS/Components/TransformComponent.h"

namespace YAML
{
	class Emitter;
	class Node;
}

namespace Avalon
{
	class Scene;

	template <typename T>
	concept DerivedFromComponent = std::is_base_of<Component, T>::value;

	class Entity
	{
	public:
		std::uint64_t id;
		std::string name;
		std::vector<std::unique_ptr<Component>> components;

	public:
		Entity(Scene* scene, uint64_t id = 0, std::string name = "", Vec3 position = Vec3(0), Vec2 rotation = Vec2(0), Vec2 scale = Vec2(1)) :
			scene(scene), id(id), name(name), transformComponent(this, position, rotation, scale)
		{}
		virtual ~Entity() {}

		const TransformComponent& GetTransform() const { return transformComponent; }
		void SetTransform(Vec3 position, Vec2 rotation, Vec2 scale) { this->transformComponent.position = position; this->transformComponent.rotation = rotation; this->transformComponent.scale = scale; }

		virtual void Initialize();
		virtual void Update(float deltaTime);
		virtual void Render(float deltaTime) const;

		virtual void Serialize(YAML::Emitter& out);
		virtual bool Deserialize(YAML::Node entityNode);

		std::string GetName() { return name; }

		template <DerivedFromComponent T, typename... Args>
		T& CreateComponent(Args... args)
		{
			auto& newComp = components.emplace_back(std::make_unique<T>(args...));
			newComp->SetOwner(this);
			return *dynamic_cast<T*>(newComp.get());
		}

	protected:
		Scene* scene;
		TransformComponent transformComponent;

	protected:
		static std::shared_ptr<Scene> GetCurrentScene();
	};
}
