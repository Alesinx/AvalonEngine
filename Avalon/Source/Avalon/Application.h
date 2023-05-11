#pragma once

#include "Core.h"

#include "Window.h"
#include "Imgui/ImguiOverlay.h"

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

		void OnEvent(Event& e);

		inline Window& GetWindow() { return *mWindow; }

	private:
		static Application* sInstance;

	private:
		bool mRunning = true;
		std::unique_ptr<Window> mWindow;
		std::unique_ptr<ImguiOverlay> mImguiOverlay;

	private:
		bool OnWindowClose(WindowCloseEvent& e);

	};

	Application* CreateApplication();
}