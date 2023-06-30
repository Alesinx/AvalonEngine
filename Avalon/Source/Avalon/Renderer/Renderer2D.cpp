#include "AvalonPch.h"
#include "Avalon/Renderer/Renderer2D.h"

#include "Avalon/Renderer/Renderer.h"
#include "Avalon/Renderer/Buffer.h"
#include "Avalon/Renderer/VertexArray.h"
#include "Avalon/Renderer/Shader.h"

#include "Platform/OpenGL/OpenGLShader.h"

namespace Avalon
{
	struct Renderer2DStorage
	{
		std::shared_ptr<VertexArray> QuadVertexArray;
		std::shared_ptr<Shader> FlatColorShader;
	};

	static Renderer2DStorage* sData;

	void Renderer2D::Init()
	{
		sData = new Renderer2DStorage();
		sData->QuadVertexArray = VertexArray::Create();

		float squareVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f
		};
		std::shared_ptr<VertexBuffer> squareVB = VertexBuffer::Create(squareVertices, sizeof(squareVertices));
		squareVB->SetLayout({
			{ ShaderDataType::Float3, "a_Position" }
		});
		sData->QuadVertexArray->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<IndexBuffer> squareIB = IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
		sData->QuadVertexArray->SetIndexBuffer(squareIB);

		sData->FlatColorShader = Shader::Create("C:\\dev\\Avalon\\Sandbox\\Asset\\Shaders\\FlatColor.glsl");
	}

	void Renderer2D::Shutdown()
	{
		delete sData;
	}

	void Renderer2D::BeginScene(const OrthographicCamera& camera)
	{
		std::shared_ptr<OpenGLShader> openglShader = std::dynamic_pointer_cast<OpenGLShader>(sData->FlatColorShader);
		openglShader->Bind();
		openglShader->UploadUniformMat4("u_ViewProjection", camera.GetViewProjecionMatrix());
		openglShader->UploadUniformMat4("u_Transform", Mat4(1.0f));
	}

	void Renderer2D::EndScene()
	{
	}

	void Renderer2D::DrawQuad(const Vec2& position, const Vec2& size, const Vec4& color)
	{
		DrawQuad({position.x, position.y, 0.0f}, size, color);
	}

	void Renderer2D::DrawQuad(const Vec3& position, const Vec2& size, const Vec4& color)
	{
		std::shared_ptr<OpenGLShader> openglShader = std::dynamic_pointer_cast<OpenGLShader>(sData->FlatColorShader);
		openglShader->Bind();
		openglShader->UploadUniformFloat4("u_Color", color);

		sData->QuadVertexArray->Bind();
		Renderer::DrawIndexed(sData->QuadVertexArray);
	}
}
