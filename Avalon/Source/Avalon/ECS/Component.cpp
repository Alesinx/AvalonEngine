#include "AvalonPch.h"
#include "Component.h"
#include "Avalon/ECS/Entity.h"
#include "Avalon/Renderer/Renderer2D.h"

namespace Avalon
{
	void QuadComponent::Render()
	{
		Vec2 ownerPos = mOwningEntity->GetTransform().position;
		Renderer2D::DrawQuad(ownerPos, size, color);
	}
}