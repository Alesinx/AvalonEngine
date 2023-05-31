#pragma once

#include "Core.h"

#include "Avalon/Window.h"
#include "Avalon/Imgui/ImguiOverlay.h"
#include "Avalon/Renderer/Shader.h"
#include "Avalon/Renderer/RenderBuffer.h"

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

		bool mRunning = true;
		std::unique_ptr<Window> mWindow;
		std::unique_ptr<ImguiOverlay> mImguiOverlay;
		unsigned int mVertexArray;
		std::unique_ptr<VertexBuffer> mVertexBuffer;
		std::unique_ptr<IndexBuffer> mIndexBuffer;
		std::unique_ptr<Shader> mShader;

	private:
		void Gameloop();
		bool OnWindowClose(WindowCloseEvent& e);
	};

	Application* CreateApplication();
}