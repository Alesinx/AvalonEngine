#pragma once

#include "Avalon/Core.h"
#include "Avalon/Window.h"
#include "Avalon/Imgui/ImguiOverlay.h"

#include "Avalon/Renderer/Shader.h"
#include "Avalon/Renderer/Buffer.h"
#include "Avalon/Renderer/VertexArray.h"
#include "Avalon/Renderer/Texture.h"
#include "Avalon/Renderer/OrthographicCamera.h"

namespace Avalon
{
	class Application
	{
	public:
		static inline Application& GetInstance() { return *sInstance; }

	public:
		Application();
		virtual ~Application() = default;

		void Run();

		inline const Window& GetWindow() { return *mWindow; }
		virtual void ProcessEvent(Event& e);
		
	protected:
		bool mImguiEnabled = true;

	protected:
		virtual void ProcessInput() {}
		virtual void Update();
		virtual void Render(float deltaTime);

	private:
		static Application* sInstance;

	private:
		bool mRunning = true;
		std::unique_ptr<Window> mWindow;
		std::unique_ptr<ImguiOverlay> mImguiOverlay;
		float mLastFrameTime = 0.0f;

	private:
		void Gameloop();
		bool OnWindowClose(WindowCloseEvent& e);
	};

	Application* CreateApplication();
}