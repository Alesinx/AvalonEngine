#pragma once

#include "Avalon/Renderer/RenderCommand.h"
#include "Avalon/Renderer/RendererAPI.h"

namespace Avalon
{
	class Renderer
	{
	public:
		static void BeginScene();
		static void EndScene();
		static void Submit(const std::shared_ptr<VertexArray> vertexArray);

		static inline RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

		static inline void SetClearColor() { sRendererAPI->SetClearColor(); }
		static inline void Clear() { sRendererAPI->Clear(); }
		static inline void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) { sRendererAPI->DrawIndexed(vertexArray); }

	private:
		static RendererAPI* sRendererAPI;
	};
}
