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
		mWindow->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));

		mImguiOverlay = std::make_unique<ImguiOverlay>();
		mImguiOverlay->Initialize();
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		while (mRunning)
		{
			glClearColor(1, 1, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			mImguiOverlay->Render();
			mWindow->OnUpdate();
		}
	}

	void Application::OnEvent(Event& e)
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
