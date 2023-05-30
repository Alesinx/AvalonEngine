#include "AvalonPch.h"
#include "Application.h"
#include "Avalon/Event/ApplicationEvents.h"

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

		//glGenVertexArrays(1, &mVertexArray);
		//glBindVertexArray(mVertexArray);

		float verticesPositions[2 * 3] = {
			-0.5f, -0.5f,
			 0.5f, -0.5f,
			 0.0f,  0.5f,
		};
		glGenBuffers(1, &mVertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(verticesPositions), verticesPositions, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), nullptr);

		//glGenBuffers(1, &mIndexBuffer);
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffer);

		//unsigned int indices[3] = { 0, 1, 2 };
		//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			out vec3 v_Position;
			void main()
			{
				v_Position = a_Position;
				gl_Position = vec4(a_Position, 1.0);	
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core

			in vec3 v_Position;
			layout(location = 0) out vec4 color;
			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
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
		glDrawArrays(GL_TRIANGLES, 0, 3);
		//glBindVertexArray(mVertexArray);
		//glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

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
