#include "AvalonPch.h"
#include "Renderer.h"

#include "Avalon/Renderer/RenderCommand.h"
#include "Platform//OpenGL/OpenGLRendererAPI.h"

namespace Avalon
{
	RendererAPI* Renderer::sRendererAPI = new OpenGLRendererAPI;

	void Renderer::BeginScene()
	{
	}

	void Renderer::EndScene()
	{
	}

	void Renderer::Submit(const std::shared_ptr<VertexArray> vertexArray)
	{
		vertexArray->Bind();

		DrawIndexed(vertexArray);
	}
}
