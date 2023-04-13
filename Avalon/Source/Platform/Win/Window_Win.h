#pragma once

#include "Avalon/Window.h"
#include <GLFW/glfw3.h>

namespace Avalon
{
	class Window_Win : public Window
	{
	public:
		Window_Win(const WindowProperties& properties);
		virtual ~Window_Win();

		void OnUpdate() override;

		void* GetNativeWindow() const override { return m_window; };
		unsigned int GetWidth() const override;
		unsigned int GetHeight() const override;

		void SetVSync(bool enabled) override;
		bool IsVSyncEnabled() const override;

	private:
		void Init(const WindowProperties& properties);
		void Shutdown();

	private:
		GLFWwindow* m_window;
		WindowProperties m_windowProperties;
	};
}