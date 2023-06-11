#include "AvalonPch.h"
#include "Renderer.h"

#include "Avalon/Renderer/RenderCommand.h"
#include "Platform//OpenGL/OpenGLRendererAPI.h"
#include "Platform//OpenGL/OpenGLShader.h"

namespace Avalon
{
	RendererAPI* Renderer::sRendererAPI = new OpenGLRendererAPI;

	void Renderer::BeginScene()
	{
	}

	void Renderer::EndScene()
	{
	}

	void Renderer::Submit(const std::shared_ptr<Shader> shader, const std::shared_ptr<VertexArray>& vertexArray, const Mat4& transform)
	{
		shader->Bind();

		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_Transform", transform);

		vertexArray->Bind();
		DrawIndexed(vertexArray);
	}
}
