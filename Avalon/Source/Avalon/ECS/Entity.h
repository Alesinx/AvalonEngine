#pragma once

#include "Avalon/ECS/Components/Component.h"
#include "Avalon/ECS/Components/TransformComponent.h"

namespace YAML
{
	class Emitter;
}

namespace Avalon
{
	template <typename T>
	concept DerivedFromComponent = std::is_base_of<Component, T>::value;

	class Entity
	{
	public:
		Entity(uint64_t id = 0, std::string name = "", Vec3 position = Vec3(0), Vec2 rotation = Vec2(0), Vec2 scale = Vec2(1)) :
			id(id), name(name), transformComponent(this, position, rotation, scale)
		{}
		virtual ~Entity() {}

		const TransformComponent& GetTransform() const { return transformComponent; }
		void SetTransform(Vec3 position, Vec2 rotation, Vec2 scale) { this->transformComponent.position = position; this->transformComponent.rotation = rotation; this->transformComponent.scale = scale; }

		virtual void Initialize();
		virtual void Update(float deltaTime);
		virtual void Render(float deltaTime) const;

		virtual void Serialize(YAML::Emitter& out);
		virtual void Deserialize();

		std::string GetName() { return name; }

		template <DerivedFromComponent T, typename... Args>
		void CreateComponent(Args... args)
		{
			auto newComp = std::make_unique<T>(this, args...);
			newComp->SetOwner(this);
			components.push_back(std::move(newComp));
		}

	protected:
		TransformComponent transformComponent;

	public:
		std::uint64_t id;
		std::string name;
		std::vector<std::unique_ptr<Component>> components;
	};
}
