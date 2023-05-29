#pragma once

#include "Avalon/Window.h"
#include "Avalon/Renderer/GraphicsContext.h"
#include <GLFW/glfw3.h>

namespace Avalon
{
	class WindowWin : public Window
	{
	public:
		WindowWin(const WindowProperties& properties);
		virtual ~WindowWin();

		void OnUpdate() override;

		void* GetNativeWindow() const override { return mGLFWWindow; };
		unsigned int GetWidth() const override { return mWindowProperties.width; }
		unsigned int GetHeight() const override { return mWindowProperties.height; }

		inline void SetEventCallback(const std::function<void(Event&)>& callback) override { mWindowProperties.eventCallback = callback; }
		void SetVSync(bool enabled) override;
		bool IsVSyncEnabled() const override { return mWindowProperties.bVSync; }

	private:
		void Init(const WindowProperties& properties);
		void Shutdown();
		void SetGLFWCallbacks();

	private:
		GLFWwindow* mGLFWWindow;
		GraphicsContext* mContext;
		WindowProperties mWindowProperties;
	};
}
