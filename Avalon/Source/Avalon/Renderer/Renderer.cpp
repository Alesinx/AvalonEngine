#include "AvalonPch.h"
#include "Renderer.h"

#include "Avalon/Renderer/Renderer2D.h"
#include "Platform//OpenGL/OpenGLRendererAPI.h"
#include "Platform//OpenGL/OpenGLShader.h"

namespace Avalon
{
	RendererAPI* Renderer::sRendererAPI = new OpenGLRendererAPI;
	std::unique_ptr<Renderer::SceneData> Renderer::sSceneData = std::make_unique<Renderer::SceneData>();

	void Renderer::Initialize()
	{
		sRendererAPI->Initialize();
		Renderer2D::Init();
	}

	void Renderer::BeginScene(OrthographicCamera& camera)
	{
		sSceneData->ViewProjectionMatrix = camera.GetViewProjecionMatrix();
	}

	void Renderer::EndScene()
	{
	}

	void Renderer::Submit(const std::shared_ptr<Shader> shader, const std::shared_ptr<VertexArray>& vertexArray, const Mat4& transform)
	{
		shader->Bind();

		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_ViewProjection", sSceneData->ViewProjectionMatrix);
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_Transform", transform);

		vertexArray->Bind();
		DrawIndexed(vertexArray);
	}

	void Renderer::OnWindowResize(uint32_t width, uint32_t height)
	{
		sRendererAPI->SetViewport(0, 0, width, height);
	}
}
