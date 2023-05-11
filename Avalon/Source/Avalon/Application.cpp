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
		mWindow->SetEventCallback(BIND_EVENT_FN(OnEvent));
		mImguiOverlay = std::unique_ptr<ImguiOverlay>(new ImguiOverlay());
		mImguiOverlay->Initialize();
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		while (m_running)
		{
			mWindow->OnUpdate();
			mImguiOverlay->Update();
		}
	}
}
