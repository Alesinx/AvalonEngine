#pragma once

#include "Avalon/Core.h"
#include "Avalon/Window.h"
#include "Avalon/Imgui/ImguiOverlay.h"
#include "Avalon/Renderer/Shader.h"
#include "Avalon/Renderer/Buffer.h"
#include "Avalon/Renderer/VertexArray.h"
#include "Avalon/Renderer/Texture.h"

namespace Avalon
{
	class Application
	{
	public:
		static inline Application& GetInstance() { return *sInstance; }

		Application();
		virtual ~Application() = default;

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

		std::shared_ptr<Shader> mTriangleShader;
		std::shared_ptr<VertexArray> mTriangleVA;
		std::shared_ptr<Shader> mBlueShader;
		std::shared_ptr<VertexArray> mSquareVA;

		std::shared_ptr<Texture2D> mTexture;
		std::shared_ptr<Shader> mTextureShader;

	private:
		void Gameloop();
		bool OnWindowClose(WindowCloseEvent& e);
	};

	Application* CreateApplication();
}