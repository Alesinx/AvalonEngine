#include "AvalonPch.h"
#include "Component.h"
#include "Avalon/ECS/Entity.h"
#include "Avalon/Renderer/Renderer2D.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Avalon
{
	void QuadComponent::Initialize()
	{
	}

	void QuadComponent::Update(float deltaTime)
	{
	}

	void QuadComponent::Render(float deltaTime)
	{
		Vec3 ownerPos = mOwningEntity->GetTransform().position;
		Vec2 ownerScale = mOwningEntity->GetTransform().scale;
		Renderer2D::DrawQuad(ownerPos, ownerScale * size, color);
	}

	void SpriteComponent::Initialize()
	{
		texture2D = Avalon::Texture2D::Create("Assets/Textures/Fish.png");
	}

	void SpriteComponent::Update(float deltaTime)
	{
	}

	void SpriteComponent::Render(float deltaTime)
	{
		Vec3 ownerPos = mOwningEntity->GetTransform().position;
		Vec2 ownerScale = mOwningEntity->GetTransform().scale;
		Renderer2D::DrawQuad(ownerPos, ownerScale, texture2D);
	}

	void VerticalMovementComponent::Initialize()
	{
		originalPosition = mOwningEntity->GetTransform().position;
	}

	void VerticalMovementComponent::Update(float deltaTime)
	{
		Vec3 currentPosition = mOwningEntity->GetTransform().position;
		currentPosition.y += direction * speed * deltaTime;
		float offset = glm::abs(currentPosition.y - originalPosition.y);
		if (offset > maxOffset)
		{
			currentPosition.y = direction * maxOffset;
			direction *= -1;
		}

		Vec2 originalRotation = mOwningEntity->GetTransform().rotation;
		Vec2 originalScale = mOwningEntity->GetTransform().scale;
		mOwningEntity->SetTransform(Transform(currentPosition, originalRotation, originalScale));
	}

	void VerticalMovementComponent::Render(float deltaTime)
	{
	}
}