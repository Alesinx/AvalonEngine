#include "AvalonPch.h"
#include "Avalon/ECS/Entity.h"
#include "Avalon/ECS/Components/SpriteComponent.h"
#include "Avalon/ECS/Components/Component.h"
#include "Avalon/Renderer/Renderer2D.h"

namespace Avalon
{
	void SpriteComponent::Initialize()
	{
		texture2D = Avalon::Texture2D::Create(texturePath);
	}

	void SpriteComponent::Update(float deltaTime)
	{
	}

	void SpriteComponent::Render(float deltaTime)
	{
		Vec3 ownerPos = mOwningEntity->GetTransform().position;
		Vec2 ownerScale = mOwningEntity->GetTransform().scale;
		Renderer2D::DrawQuad(ownerPos, ownerScale, texture2D, tintColor);
	}
}