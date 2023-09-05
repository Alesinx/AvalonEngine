#pragma once

#include "Avalon/ECS/Component.h"

namespace Avalon
{
	struct Transform
	{
		Transform(Vec3 position, Vec2 rotation, Vec2 scale) : position(position), rotation(rotation), scale(scale) {}

		Vec3 position = Vec3(0);
		Vec2 rotation = Vec2(0);
		Vec2 scale = Vec2(1);
	};

	class Entity
	{
	public:
		Entity(Vec3 position = Vec3(0), Vec2 rotation = Vec2(0), Vec2 scale = Vec2(1)) :
			mTransform(position, rotation, scale)
		{}

		const Transform& GetTransform() const { return mTransform; }

		void Render() const;

		void AddComponent(Component* component);

	private:
		Transform mTransform;
		std::vector<Component*> mComponents;
	};
}

