#pragma once

#include "Avalon/Core/Core.h"
#include "OrthographicCamera.h"

namespace Avalon
{
	class Renderer2D
	{
	public:
		static void Init();
		static void Shutdown();

		static void BeginScene(const OrthographicCamera& camera);
		static void EndScene();;

		static void DrawQuad(const Vec2& position, const Vec2& size, const Vec4& color);
		static void DrawQuad(const Vec3& position, const Vec2& size, const Vec4& color);
	};
}
