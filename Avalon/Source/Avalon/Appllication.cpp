#include "AvalonPch.h"
#include "Application.h"
#include "Avalon/Event/ApplicationEvents.h"
#include <glad/glad.h>

namespace Avalon 
{
	Application::Application()
	{
		mWindow = std::unique_ptr<Window>(Window::Create());
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		while (m_running)
		{
			mWindow->OnUpdate();
		}
	}
}
