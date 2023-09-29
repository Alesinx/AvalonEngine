#include "AvalonPch.h"
#include "Application.h"
#include "Avalon/Event/ApplicationEvents.h"
#include "Avalon/Renderer/Renderer.h"
#include "Avalon/Time/Time.h"

// Will probably need to be removed in the future
#include <glfw/glfw3.h>
#include "Platform/OpenGL/OpenGLShader.h"
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>

namespace Avalon 
{
	Application* Application::sInstance = nullptr;

	Application::Application(const std::string& name)
	{
		AVALON_CORE_INFO("Creating application with name {0}", name);

		AVALON_CORE_ASSERT(!sInstance, "Application already exists");
		sInstance = this;

		mWindow = Window::Create(WindowProperties(name));
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
		mLastFrameTime = Time::GetCurrentTime();

		while (mRunning)
		{
			float time = Time::GetCurrentTime();
			float deltaTime = time - mLastFrameTime;
			mLastFrameTime = time;

			// Input
			ProcessInput();

			// Simulation
			InternalUpdate(deltaTime);

			// Rendering
			InternalRender(deltaTime);
		}
	}

	void Application::EditorUpdate(float deltaTime)
	{
	}

	void Application::Update(float deltaTime)
	{
	}

	void Application::InternalRender(float deltaTime)
	{
		Render(deltaTime);

		if (mOverlayEnabled)
		{
			mImguiOverlay->Begin();
			ImguiRender(deltaTime);
			mImguiOverlay->End();
		}
	}

	void Application::InternalUpdate(float deltaTime)
	{
		mWindow->OnUpdate();

		if(InEditMode)
		{
			EditorUpdate(deltaTime);
		}
		else
		{
			Update(deltaTime);
		}
	}

	void Application::Render(float deltaTime)
	{
	}

	std::shared_ptr<Scene>& Application::CreateScene(const std::string& serializedScenePath)
	{
		scene = std::make_shared<Scene>();
		scene->Deserialize(serializedScenePath);
		return scene;
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
		minimized = e.GetWidth() == 0 || e.GetHeight() == 0;
		if (minimized)
		{
			return false;
		}

		Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());
		return false;
	}
}
