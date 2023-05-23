#pragma once

#include "Core.h"

#include "Window.h"
#include "Imgui/ImguiOverlay.h"

namespace Avalon
{
	class Application
	{
	public:
		static inline Application& GetInstance() { return *sInstance; }

		Application();
		virtual ~Application();

		void Run();
		void OnEvent(Event& e);

		inline const Window& GetWindow() { return *mWindow; }

	private:
		static Application* sInstance;

		bool mRunning = true;
		std::unique_ptr<Window> mWindow;
		std::unique_ptr<ImguiOverlay> mImguiOverlay;

	private:
		bool OnWindowClose(WindowCloseEvent& e);

	};

	Application* CreateApplication();
}