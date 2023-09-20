#include "AvalonPch.h"
#include "Component.h"
#include "Avalon/ECS/Entity.h"
#include "Avalon/Renderer/Renderer2D.h"
#include <yaml-cpp/yaml.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Avalon
{
	void QuadComponent::Initialize()
	{
	}

	void QuadComponent::Render(float deltaTime)
	{
		Vec3 ownerPos = mOwningEntity->GetTransform().position;
		Vec2 ownerScale = mOwningEntity->GetTransform().scale;
		Renderer2D::DrawQuad(ownerPos, ownerScale * size, color);
	}

	void QuadComponent::Serialize(YAML::Emitter& out)
	{
		out << YAML::BeginMap;

		out << YAML::Key << "QuadComponent" << YAML::Value << YAML::BeginMap;

		out << YAML::Key << "size" << YAML::Value << "{1.0f, 1.0f, 1.0f}";
		out << YAML::Key << "color" << YAML::Value << "{1.0f, 1.0f, 1.0f, 1.0f}";

		out << YAML::EndMap; // QuadComponent

		out << YAML::EndMap;
	}

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