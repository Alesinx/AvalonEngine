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

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	};
}
