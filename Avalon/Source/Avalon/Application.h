#pragma once

#include "Core.h"
#include "Window.h"

class ImguiOverlay;

namespace Avalon
{
	class Application
	{
	public:
		inline static Application& GetInstance() { return *sInstance; }

	public:
		Application();
		virtual ~Application();

		void Run();

		inline Window& GetWindow() { return *mWindow; }

	private:
		static Application* sInstance;

	private:
		bool m_running = true;
		std::unique_ptr<Window> mWindow;
		std::unique_ptr<ImguiOverlay> mImguiOverlay;
	};

	Application* CreateApplication();
}