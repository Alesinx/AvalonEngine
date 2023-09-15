#include "AvalonPch.h"
#include "Avalon/Renderer/Renderer2D.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Avalon
{
	std::unique_ptr<Renderer2DStorage> Renderer2D::sData = nullptr;
	float Renderer2D::alphaThreshold = 0.5f;

	void Renderer2D::Init()
	{
		sData = std::unique_ptr<Renderer2DStorage>(new Renderer2DStorage());
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
	}

	void Renderer2D::BeginScene(const OrthographicCamera& camera)
	{
		sData->TextureShader->Bind();
		sData->TextureShader->SetMat4("u_ViewProjection", camera.GetViewProjecionMatrix());
		sData->TextureShader->SetFloat("u_AlphaThreshold", alphaThreshold);
	}

	void Renderer2D::EndScene()
	{
	}

	void Renderer2D::DrawQuad(const Vec2& position, const Vec2& size, const Vec4& color)
	{
		DrawQuad({position.x, position.y, 0.0f}, size, color);
	}

	void Renderer2D::DrawQuad(const Vec2& position, const Vec2& size, const std::shared_ptr<Texture2D>& texture, const Vec4& tintColor)
	{
		DrawQuad({ position.x , position.y, 0.0f }, size, texture, tintColor);
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

	void Renderer2D::DrawQuad(const Vec3& position, const Vec2& size, const std::shared_ptr<Texture2D>& texture, const Vec4& tintColor)
	{
		texture->Bind();

		const Mat4 transform = glm::translate(Mat4(1.0f), position) * glm::scale(Mat4(1.0f), { size.x, size.y, 1.0f });
		sData->TextureShader->SetMat4("u_Transform", transform);
		sData->TextureShader->SetFloat4("u_Color", tintColor);

		sData->QuadVertexArray->Bind();
		Renderer::DrawIndexed(sData->QuadVertexArray);
	}
}
