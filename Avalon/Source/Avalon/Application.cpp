#include "AvalonPch.h"
#include "Application.h"
#include "Avalon/Event/ApplicationEvents.h"
#include "Avalon/Renderer/Renderer.h"

// Will probably need to be removed in the future
#include "Platform/OpenGL/OpenGLShader.h"
#include <glad/glad.h>

namespace Avalon 
{
	Application* Application::sInstance = nullptr;

	Application::Application()
	{
		AVALON_CORE_ASSERT(!sInstance, "Application already exists");
		
		sInstance = this;

		mWindow = std::unique_ptr<Window>(Window::Create());
		mWindow->SetEventCallback(BIND_EVENT_FN(Application::ProcessEvent));

		mImguiOverlay = std::make_unique<ImguiOverlay>();
		mImguiOverlay->Initialize();

		/////////////////////////////////////////////////////////////////////////////
		// mVertexArray /////////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////////////

		mVertexArray = std::shared_ptr<VertexArray>(VertexArray::Create());

		const float vertices[3 * 7] = {
			// Position  | Color
			-0.5f, -0.5f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		std::shared_ptr<VertexBuffer> vertexBuffer = std::shared_ptr<VertexBuffer>(VertexBuffer::Create(vertices, sizeof(vertices)));
		vertexBuffer->SetLayout(
			{
				{ ShaderDataType::Float2, "a_position" },
				{ ShaderDataType::Float4, "a_color"}
			}
		);
		mVertexArray->AddVertexBuffer(vertexBuffer);
		
		const uint32_t indices[3] = { 0, 1, 2 };
		std::shared_ptr<IndexBuffer> indexBuffer = std::shared_ptr<IndexBuffer>(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		mVertexArray->SetIndexBuffer(indexBuffer);

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec2 a_position;
			layout(location = 1) in vec4 a_color;

			out vec2 v_position;
			out vec4 v_color;

			void main()
			{
				v_position = a_position;
				v_color = a_color;
				gl_Position = vec4(a_position, 1.0, 1.0);
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec2 v_position;
			in vec4 v_color;

			void main()
			{
				//color = vec4(v_position * 0.5 + 0.5, 1.0, 1.0);
				color = v_color;
			}
		)";

		mShader = std::shared_ptr<Shader>(Shader::Create(vertexSrc, fragmentSrc));

		/////////////////////////////////////////////////////////////////////////////
		// mSquareVA ////////////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////////////

		mSquareVA = std::shared_ptr<VertexArray>(VertexArray::Create());

		float squareVertices[4 * 4] = {
			-0.5f,  0.5f,  0.0f,  1.0f,
			-0.5f, -0.5f,  0.0f,  0.0f,
			 0.5f, -0.5f,  1.0f,  0.0f,
			 0.5f,  0.5f,  1.0f,  1.0f
		};

		std::shared_ptr<VertexBuffer> squareVB = std::shared_ptr<VertexBuffer>(VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVB->SetLayout(
			{
				{ ShaderDataType::Float2, "a_position" },
				{ ShaderDataType::Float2, "a_TexCoord" }
			}
		);
		mSquareVA->AddVertexBuffer(squareVB);

		const uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<IndexBuffer> squareIB = std::shared_ptr<IndexBuffer>(IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		mSquareVA->SetIndexBuffer(squareIB);

		std::string blueShaderVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec2 a_position;

			out vec2 v_position;

			void main()
			{
				v_position = a_position;
				gl_Position = vec4(a_position, 1.0, 1.0);
			}
		)";

		std::string blueShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			void main()
			{
				color = vec4(0.2, 0.3, 0.8, 1.0);
			}
		)";

		mBlueShader = std::shared_ptr<Shader>(Shader::Create(blueShaderVertexSrc, blueShaderFragmentSrc));

		/////////////////////////////////////////////////////////////////////////////
		// Texture //////////////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////////////

		std::string textureShaderVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec2 a_Position;
			layout(location = 1) in vec2 a_TexCoord;
			out vec2 v_TexCoord;
			void main()
			{
				v_TexCoord = a_TexCoord;
				gl_Position = vec4(a_Position, 1.0, 1.0);
			}
		)";

		std::string textureShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			in vec2 v_TexCoord;
			
			uniform sampler2D u_Texture;
			void main()
			{
				color = texture(u_Texture, v_TexCoord);
			}
		)";

		mTextureShader = std::shared_ptr<Shader>(Shader::Create(textureShaderVertexSrc, textureShaderFragmentSrc));
		mTexture = std::shared_ptr<Texture2D>(Texture2D::Create("C:\\Dev\\AvalonEngine\\Avalon\\Assets\\Textures\\Checkerboard.png"));

		std::shared_ptr<OpenGLShader> oglShader = std::dynamic_pointer_cast<OpenGLShader>(mTextureShader);
		oglShader->Bind();
		oglShader->UploadUniformInt("u_Texture", 0);
	}

	void Application::Run()
	{
		while (mRunning)
		{
			Gameloop();
		}
	}

	void Application::Gameloop()
	{
		ProcessInput();
		Update();
		Render();
	}

	void Application::ProcessInput()
	{

	}

	void Application::Update()
	{
		mWindow->OnUpdate();
	}

	void Application::Render()
	{
		Renderer::SetClearColor();
		Renderer::Clear();

		Renderer::BeginScene();

		mTexture->Bind();
		Renderer::Submit(mTextureShader, mSquareVA);

		// Render triangle
		Renderer::Submit(mShader, mVertexArray);

		// Render blue quad
		//Renderer::Submit(mBlueShader, mSquareVA);

		Renderer::EndScene();

		mImguiOverlay->Render();
	}

	void Application::ProcessEvent(Event& e)
	{
		if(!e.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose)))
		{
			mImguiOverlay->OnEvent(e);
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		mRunning = false;
		return true;
	}
}
