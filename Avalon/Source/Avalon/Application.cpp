#include "AvalonPch.h"
#include "Application.h"
#include "Avalon/Event/ApplicationEvents.h"
#include "Avalon/Renderer/Renderer.h"

// Will probably need to be removed in the future
#include <glfw/glfw3.h>
#include "Platform/OpenGL/OpenGLShader.h"
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>

namespace Avalon 
{
	Application* Application::sInstance = nullptr;

	Application::Application()
	{
		AVALON_CORE_ASSERT(!sInstance, "Application already exists");
		sInstance = this;

		mWindow = std::unique_ptr<Window>(Window::Create());
		mWindow->SetEventCallback(BIND_EVENT_FN(Application::ProcessEvent));

		mImguiOverlay = std::unique_ptr<ImguiOverlay>();
		mImguiOverlay->Initialize();

		Renderer::Initialize();
	}

	void Application::Run()
	{
		Gameloop();
	}

	void Application::Gameloop()
	{
		while (mRunning)
		{
			float time = (float)glfwGetTime();
			float deltaTime = time - mLastFrameTime;
			mLastFrameTime = time;

			// Input
			ProcessInput();

			// Simulation
			Update(deltaTime);

			// Rendering
			Renderer::SetClearColor();
			Renderer::Clear();
			Render(deltaTime);
			if (mImguiEnabled)
				mImguiOverlay->Render();
		}
	}

	void Application::Update(float deltaTime)
	{
		mWindow->OnUpdate();
	}

	void Application::Render(float deltaTime)
	{
	}

	void Application::ProcessEvent(Event& e)
	{
		if (e.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose)))
			return;

		if (e.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(Application::OnWindowResize)))
			return;

		if (mImguiEnabled)
			mImguiOverlay->OnEvent(e);
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		mRunning = false;
		return true;
	}
	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		mMinimized = e.GetWidth() == 0 || e.GetHeight() == 0;
		if (mMinimized)
			return false;

		Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());
		return false;
	}
}
