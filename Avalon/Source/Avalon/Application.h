#pragma once

#include "Core.h"
#include "Window.h"

namespace Avalon
{
	class Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

	private:
		std::unique_ptr<Window> mWindow;
		bool m_running = true;
	};

	Application* CreateApplication();
}