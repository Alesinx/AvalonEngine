#include "AvalonPch.h"
#include "Renderer.h"

#include "Avalon/Renderer/RenderCommand.h"

namespace Avalon
{
	void Renderer::BeginScene()
	{
	}

	void Renderer::EndScene()
	{
	}

	void Renderer::Submit(const std::shared_ptr<VertexArray> vertexArray)
	{
		vertexArray->Bind();

		RenderCommand::DrawIndexed(vertexArray);
	}
}
