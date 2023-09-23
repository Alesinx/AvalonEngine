#include "AvalonPch.h"
#include "Avalon/ECS/Components/VerticalMovementComponent.h"
#include "Avalon/ECS/Entity.h"
#include "Avalon/Renderer/Renderer2D.h"

#include <yaml-cpp/yaml.h>

namespace Avalon
{
	void VerticalMovementComponent::Initialize()
	{
		currentOffset = initialOffset;
		originalPosition = mOwningEntity->GetTransform().position;
	}

	void VerticalMovementComponent::Update(float deltaTime)
	{
		currentOffset += direction * speed * deltaTime;
		if (glm::abs(currentOffset) >= maxOffset)
		{
			currentOffset = direction * maxOffset;
			direction *= -1;
		}

		Vec3 currentPosition = originalPosition + Vec3(0.f, currentOffset, 0.f);
		Vec2 originalRotation = mOwningEntity->GetTransform().rotation;
		Vec2 originalScale = mOwningEntity->GetTransform().scale;
		mOwningEntity->SetTransform(currentPosition, originalRotation, originalScale);
	}

	void VerticalMovementComponent::Serialize(YAML::Emitter& out)
	{
		out << YAML::BeginMap;

		out << YAML::Key << "VerticalMovementComponent" << YAML::Value << YAML::BeginMap;

		out << YAML::Key << "movingDown" << YAML::Value << (direction == 1);
		out << YAML::Key << "initialOffset" << YAML::Value << initialOffset;
		out << YAML::Key << "maxOffset" << YAML::Value << maxOffset;
		out << YAML::Key << "speed" << YAML::Value << speed;

		out << YAML::EndMap; // VerticalMovementComponent

		out << YAML::EndMap;
	}

	void VerticalMovementComponent::Deserialize(YAML::Node verticalMovementComponentNode)
	{
		direction = verticalMovementComponentNode["movingDown"].as<bool>()? 1 : -1;
		initialOffset = verticalMovementComponentNode["initialOffset"].as<float>();
		maxOffset = verticalMovementComponentNode["maxOffset"].as<float>();
		speed = verticalMovementComponentNode["speed"].as<float>();
	}
}