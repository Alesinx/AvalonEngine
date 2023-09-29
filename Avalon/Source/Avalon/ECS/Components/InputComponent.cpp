#include "AvalonPch.h"
#include "Avalon/ECS/Components/MovementComponent.h"
#include "Avalon/ECS/Components/TransformComponent.h"
#include "Avalon/ECS/Entity.h"
#include "Avalon/Input/Input.h"
#include "Avalon/Input/InputKeys.h"

#include <yaml-cpp/yaml.h>

namespace Avalon
{
	void InputComponent::Update(float deltaTime)
	{
		if (Input::IsKeyPressed(AVALON_KEY_A))
		{
			Vec3 newPos = mOwningEntity->GetPosition();
			newPos.x -= speed * deltaTime;
			mOwningEntity->SetPosition(newPos);
		}
		if (Input::IsKeyPressed(AVALON_KEY_S))
		{
			Vec3 newPos = mOwningEntity->GetPosition();
			newPos.y -= speed * deltaTime;
			mOwningEntity->SetPosition(newPos);
		}
		if (Input::IsKeyPressed(AVALON_KEY_D))
		{
			Vec3 newPos = mOwningEntity->GetPosition();
			newPos.x += speed * deltaTime;
			mOwningEntity->SetPosition(newPos);
		}
		if (Input::IsKeyPressed(AVALON_KEY_W))
		{
			Vec3 newPos = mOwningEntity->GetPosition();
			newPos.y += speed * deltaTime;
			mOwningEntity->SetPosition(newPos);
		}
	}

	void InputComponent::Serialize(YAML::Emitter& out)
	{
		out << YAML::BeginMap;

		out << YAML::Key << "MovementComponent" << YAML::Value << YAML::BeginMap;

		out << YAML::Key << "speed" << YAML::Value << speed;

		out << YAML::EndMap; // SpriteComponent

		out << YAML::EndMap;
	}

	void InputComponent::Deserialize(const YAML::Node& movementComponentNode)
	{
		speed = movementComponentNode["speed"].as<float>();
	}
}