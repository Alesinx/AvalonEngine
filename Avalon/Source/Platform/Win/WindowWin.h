#pragma once

#include "Avalon/Window.h"
#include <GLFW/glfw3.h>

namespace Avalon
{
	class WindowWin : public Window
	{
	public:
		WindowWin(const WindowProperties& properties);
		virtual ~WindowWin();

		void OnUpdate() override;

		void* GetNativeWindow() const override { return mWindow; };
		unsigned int GetWidth() const override;
		unsigned int GetHeight() const override;

		void SetVSync(bool enabled) override;
		bool IsVSyncEnabled() const override;

	private:
		void Init(const WindowProperties& properties);
		void Shutdown();

	private:
		GLFWwindow* mWindow;
		WindowProperties mWindowProperties;
	};
}
