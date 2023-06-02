#include "AvalonPch.h"
#include "Application.h"
#include "Avalon/Event/ApplicationEvents.h"

#include <glad/glad.h>

namespace Avalon 
{
	Application* Application::sInstance = nullptr;

	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
		case Avalon::ShaderDataType::Float:
			return GL_FLOAT;
		case Avalon::ShaderDataType::Float2:
			return GL_FLOAT;
		case Avalon::ShaderDataType::Float3:
			return GL_FLOAT;
		case Avalon::ShaderDataType::Float4:
			return GL_FLOAT;
		case Avalon::ShaderDataType::Mat3:
			return GL_FLOAT;
		case Avalon::ShaderDataType::Mat4:
			return GL_FLOAT;
		case Avalon::ShaderDataType::Int:
			return GL_INT;
		case Avalon::ShaderDataType::Int2:
			return GL_INT;
		case Avalon::ShaderDataType::Int3:
			return GL_INT;
		case Avalon::ShaderDataType::Int4:
			return GL_INT;
		case Avalon::ShaderDataType::Bool:
			return GL_BOOL;
		}

		AVALON_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	Application::Application()
	{
		AVALON_CORE_ASSERT(!sInstance, "Application already exists");
		
		sInstance = this;

		mWindow = std::unique_ptr<Window>(Window::Create());
		mWindow->SetEventCallback(BIND_EVENT_FN(Application::ProcessEvent));

		mImguiOverlay = std::make_unique<ImguiOverlay>();
		mImguiOverlay->Initialize();

		const float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		glGenVertexArrays(1, &mVertexArray);
		glBindVertexArray(mVertexArray);

		mVertexBuffer = std::unique_ptr<VertexBuffer>(VertexBuffer::Create(vertices, sizeof(vertices)));

		mVertexBuffer->SetLayout(
			{
				{ ShaderDataType::Float2, "a_position" },
				{ ShaderDataType::Float4, "a_color"}
			}
		);

		uint32_t index = 0;
		const BufferLayout& layout = mVertexBuffer->GetLayout();
		for (const BufferElement& element : layout)
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index, 
				element.GetComponentCount(), 
				ShaderDataTypeToOpenGLBaseType(element.type), 
				element.normalized ? GL_TRUE : GL_FALSE, 
				layout.GetStride(), 
				(const void*)element.offset);
			index++;
		}
		
		const uint32_t indices[3] = { 0, 1, 2 };
		mIndexBuffer = std::unique_ptr<IndexBuffer>(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));

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

		mShader = std::unique_ptr<Shader>(new Shader(vertexSrc, fragmentSrc));
	}

	Application::~Application()
	{
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
		glClearColor(0.1f, 0.1f, 0.1f, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		mShader->Bind();
		glBindVertexArray(mVertexArray);
		glDrawElements(GL_TRIANGLES, mIndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);

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
