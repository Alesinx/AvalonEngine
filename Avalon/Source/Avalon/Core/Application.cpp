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

		mWindow = Window::Create();
		mWindow->SetEventCallback(BIND_EVENT_FN(Application::ProcessEvent));

		mImguiOverlay = std::unique_ptr<ImguiOverlay>(new ImguiOverlay());
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
			InternalRender(deltaTime);
		}
	}

	void Application::Update(float deltaTime)
	{
		mWindow->OnUpdate();
	}

	void Application::InternalRender(float deltaTime)
	{
		Render(deltaTime);

		if (mOverlayEnabled)
		{
			mImguiOverlay->Begin();
			ImguiRender();
			mImguiOverlay->End();
		}
	}

	void Application::ImguiRender()
	{
		mImguiOverlay->Render();
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

	void Application::SetShowImguiDemo(bool show)
	{
		if (mImguiOverlay)
			mImguiOverlay->showDemo = show;
	}
}
