#pragma once

#include "Avalon/Core/Core.h"
#include "Avalon/Core/Window.h"
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
		bool mOverlayEnabled;

	protected:
		virtual void ProcessInput() {}
		virtual void Update(float deltaTime);
		virtual void Render(float deltaTime);

		virtual void ImguiRender();

		void SetShowImguiDemo(bool show);

	private:
		static Application* sInstance;

	private:
		bool mRunning = true;
		bool mMinimized = false;
		std::unique_ptr<Window> mWindow;
		std::unique_ptr<ImguiOverlay> mImguiOverlay;
		float mLastFrameTime = 0.0f;

	private:
		void Gameloop();
		void InternalRender(float deltaTime);
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
	};

	Application* CreateApplication();
}