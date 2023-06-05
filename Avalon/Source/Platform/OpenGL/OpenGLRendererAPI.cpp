#include "AvalonPch.h"
#include "OpenGLRendererAPI.h"

#include <glad/glad.h>

namespace Avalon
{
	void OpenGLRendererAPI::SetClearColor()
	{
		glClearColor(0.1f, 0.1f, 0.1f, 1);
	}

	void OpenGLRendererAPI::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLRendererAPI::DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray)
	{
		glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
	}
}
