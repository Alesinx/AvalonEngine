#include "AvalonPch.h"
#include "Avalon/ECS/Components/VerticalMovementComponent.h"
#include "Avalon/ECS/Entity.h"
#include "Avalon/Renderer/Renderer2D.h"

#include <yaml-cpp/yaml.h>

namespace Avalon
{
	void VerticalMovementComponent::Initialize()
	{
		originalPosition = mOwningEntity->GetTransform().position;
	}

	void VerticalMovementComponent::Update(float deltaTime)
	{
		offset += direction * speed * deltaTime;
		if (glm::abs(offset) >= maxOffset)
		{
			offset = direction * maxOffset;
			direction *= -1;
		}

		Vec3 currentPosition = originalPosition + Vec3(0.f, offset, 0.f);
		Vec2 originalRotation = mOwningEntity->GetTransform().rotation;
		Vec2 originalScale = mOwningEntity->GetTransform().scale;
		mOwningEntity->SetTransform(Transform(currentPosition, originalRotation, originalScale));
	}

	void VerticalMovementComponent::Serialize(YAML::Emitter& out)
	{
		out << YAML::BeginMap;

		out << YAML::Key << "VerticalMovementComponent" << YAML::Value << YAML::BeginMap;

		out << YAML::Key << "initialOffset" << YAML::Value << offset;
		out << YAML::Key << "maxOffset" << YAML::Value << maxOffset;
		out << YAML::Key << "speed" << YAML::Value << speed;

		out << YAML::EndMap; // VerticalMovementComponent

		out << YAML::EndMap;
	}
}