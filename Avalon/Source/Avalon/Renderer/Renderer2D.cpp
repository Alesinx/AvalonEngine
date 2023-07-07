#include "AvalonPch.h"
#include "Avalon/Renderer/Renderer2D.h"

#include "Avalon/Renderer/Renderer.h"
#include "Avalon/Renderer/Buffer.h"
#include "Avalon/Renderer/VertexArray.h"
#include "Avalon/Renderer/Shader.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Avalon
{
	struct Renderer2DStorage
	{
		std::shared_ptr<VertexArray> QuadVertexArray;
		std::shared_ptr<Shader> TextureShader;
		std::shared_ptr<Texture2D> WhiteTexture;
	};

	static Renderer2DStorage* sData;

	void Renderer2D::Init()
	{
		sData = new Renderer2DStorage();
		sData->QuadVertexArray = VertexArray::Create();

		const float squareVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};
		std::shared_ptr<VertexBuffer> squareVB = VertexBuffer::Create(squareVertices, sizeof(squareVertices));
		squareVB->SetLayout({
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float2, "a_TexCoord"}
		});
		sData->QuadVertexArray->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<IndexBuffer> squareIB = IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
		sData->QuadVertexArray->SetIndexBuffer(squareIB);

		sData->WhiteTexture = Texture2D::Create(1, 1);
		uint32_t whiteTextureData = 0xffffffff;
		sData->WhiteTexture->SetData(&whiteTextureData, sizeof(uint32_t));

		sData->TextureShader = Shader::Create("Assets/Shaders/Texture.glsl");
		sData->TextureShader->Bind();
		sData->TextureShader->SetInt("u_Texture", 0);
	}

	void Renderer2D::Shutdown()
	{
		delete sData;
	}

	void Renderer2D::BeginScene(const OrthographicCamera& camera)
	{
		sData->TextureShader->Bind();
		sData->TextureShader->SetMat4("u_ViewProjection", camera.GetViewProjecionMatrix());
	}

	void Renderer2D::EndScene()
	{
	}

	void Renderer2D::DrawQuad(const Vec2& position, const Vec2& size, const Vec4& color)
	{
		DrawQuad({position.x, position.y, 0.0f}, size, color);
	}

	void Renderer2D::DrawQuad(const Vec2& position, const Vec2& size, const std::shared_ptr<Texture2D>& texture)
	{
		DrawQuad({ position.x , position.y, 0.0f }, size, texture);
	}

	void Renderer2D::DrawQuad(const Vec3& position, const Vec2& size, const Vec4& color)
	{
		sData->WhiteTexture->Bind();

		const Mat4 transform = glm::translate(Mat4(1.0f), position) * glm::scale(Mat4(1.0f), {size.x, size.y, 1.0f});
		sData->TextureShader->SetMat4("u_Transform", transform);
		sData->TextureShader->SetFloat4("u_Color", color);

		sData->QuadVertexArray->Bind();
		Renderer::DrawIndexed(sData->QuadVertexArray);
	}

	void Renderer2D::DrawQuad(const Vec3& position, const Vec2& size, const std::shared_ptr<Texture2D>& texture)
	{
		texture->Bind();

		const Mat4 transform = glm::translate(Mat4(1.0f), position) * glm::scale(Mat4(1.0f), { size.x, size.y, 1.0f });
		sData->TextureShader->SetMat4("u_Transform", transform);
		sData->TextureShader->SetFloat4("u_Color", glm::vec4(0.5f));

		sData->QuadVertexArray->Bind();
		Renderer::DrawIndexed(sData->QuadVertexArray);
	}
}
