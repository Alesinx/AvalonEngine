#pragma once

#include "Avalon/Core/Core.h"
#include "Avalon/Renderer/OrthographicCamera.h"
#include "Avalon/Renderer/Texture.h"
#include "Avalon/Renderer/Renderer.h"
#include "Avalon/Renderer/Buffer.h"
#include "Avalon/Renderer/VertexArray.h"
#include "Avalon/Renderer/Shader.h"

namespace Avalon
{
	class Application;
	 
	struct Renderer2DStorage
	{
		std::shared_ptr<VertexArray> QuadVertexArray;
		std::shared_ptr<Shader> TextureShader;
		std::shared_ptr<Texture2D> WhiteTexture;
	};

	class Renderer2D
	{
	public:
		static float alphaThreshold;

	public:
		static void Init();
		static void Shutdown();

		static void BeginScene(const OrthographicCamera& camera);
		static void EndScene();;

		static void DrawQuad(const Vec2& position, const Vec2& size, const Vec4& color);
		static void DrawQuad(const Vec2& position, const Vec2& size, const std::shared_ptr<Texture2D>& texture, const Vec4& tintColor = Vec4(1.0f));
		static void DrawQuad(const Vec3& position, const Vec2& size, const Vec4& color);
		static void DrawQuad(const Vec3& position, const Vec2& size, const std::shared_ptr<Texture2D>& texture, const Vec4& tintColor = Vec4(1.0f));

		static void SetAlphaThreshold(float newValue) { alphaThreshold = newValue; }

	private:
		static std::unique_ptr<Renderer2DStorage> sData;
	};
}
