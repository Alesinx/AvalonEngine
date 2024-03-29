#pragma once

#include "Avalon/Renderer/RenderCommand.h"
#include "Avalon/Renderer/OrthographicCamera.h"
#include "Avalon/Renderer/RendererAPI.h"
#include "Avalon/Renderer/Shader.h"

namespace Avalon
{
	class Renderer
	{
	public:
		static void Initialize();

		static inline RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

		static void BeginScene(OrthographicCamera& camera);
		static void EndScene();
		static void Submit(const std::shared_ptr<Shader> shader,
			const std::shared_ptr<VertexArray>& vertexArray,
			const Mat4& transform = Mat4(1.0f));

		static void OnWindowResize(uint32_t width, uint32_t height);

		// Render commands
		static inline void SetClearColor() { sRendererAPI->SetClearColor(); }
		static inline void Clear() { sRendererAPI->Clear(); }
		static inline void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) { sRendererAPI->DrawIndexed(vertexArray); }

	private:
		static RendererAPI* sRendererAPI;

		struct SceneData
		{
			Mat4 ViewProjectionMatrix;
		};

		static std::unique_ptr<SceneData> sSceneData;
	};
}
