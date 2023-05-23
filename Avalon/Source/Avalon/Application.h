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

		inline const Window& GetWindow() { return *mWindow; }
		virtual void ProcessEvent(Event& e);

	protected:
		virtual void ProcessInput();
		virtual void Update();
		virtual void Render();

	private:
		static Application* sInstance;

		std::unique_ptr<Window> mWindow;
		std::unique_ptr<ImguiOverlay> mImguiOverlay;
		bool mRunning = true;

	private:
		void Gameloop();
		bool OnWindowClose(WindowCloseEvent& e);

	};

	Application* CreateApplication();
}