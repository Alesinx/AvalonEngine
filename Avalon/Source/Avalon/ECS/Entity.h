#pragma once

#include "Avalon/ECS/Components/Component.h"

namespace YAML
{
	class Emitter;
}

namespace Avalon
{
	class Transform
	{
	public:
		Transform(Vec3 position, Vec2 rotation, Vec2 scale) : position(position), rotation(rotation), scale(scale) {}

		Vec3 position = Vec3(0);
		Vec2 rotation = Vec2(0);
		Vec2 scale = Vec2(1);

		void Serialize(YAML::Emitter& out);
		void Deserialize();
	};

	template <typename T>
	concept DerivedFromComponent = std::is_base_of<Component, T>::value;

	class Entity
	{
	public:
		Entity(std::string name = "", Vec3 position = Vec3(0), Vec2 rotation = Vec2(0), Vec2 scale = Vec2(1)) :
			name(name), transform(position, rotation, scale)
		{}
		virtual ~Entity() {}

		const Transform& GetTransform() const { return transform; }
		void SetTransform(Transform newTransform) { this->transform = newTransform; }

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
		Transform transform;

	public:
		std::string id;
		std::string name;
		std::vector<std::unique_ptr<Component>> components;
	};
}
