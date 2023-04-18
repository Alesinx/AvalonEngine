#include "AvalonPch.h"
#include "WindowWin.h"
#include "Avalon/Core.h"
#include "Avalon/Log/Log.h"
#include <glad/glad.h>

namespace Avalon
{
	static bool s_GLFWInitialized = false;

	Window* Window::Create(const WindowProperties& properties)
	{
		return new WindowWin(properties);
	}

	Avalon::WindowWin::WindowWin(const WindowProperties& properties)
	{
		Init(properties);
	}

	Avalon::WindowWin::~WindowWin()
	{
		Shutdown();
	}

	void Avalon::WindowWin::Init(const WindowProperties& properties)
	{
		AVALON_CORE_INFO("Creating window {0} ({1}, {2})", properties.title, properties.width, properties.height);

		if (!s_GLFWInitialized)
		{
			int success = glfwInit();
			AVALON_CORE_ASSERT(success, "Could not initialize GLFW");

			s_GLFWInitialized = true;
		}

		mWindow = glfwCreateWindow((int)properties.width, properties.height, properties.title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(mWindow);

		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		AVALON_CORE_ASSERT(status, "Failed to initialize Glad");

		glfwSetWindowUserPointer(mWindow, &mWindowProperties);
		
	}

	void Avalon::WindowWin::Shutdown()
	{
		glfwDestroyWindow(mWindow);
	}

	void Avalon::WindowWin::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(mWindow);
	}

	unsigned int Avalon::WindowWin::GetWidth() const
	{
		return mWindowProperties.width;
	}

	unsigned int Avalon::WindowWin::GetHeight() const
	{
		return mWindowProperties.height;
	}

	void WindowWin::SetVSync(bool enabled)
	{
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		mWindowProperties.bVSync = enabled;
	}

	bool WindowWin::IsVSyncEnabled() const
	{
		return mWindowProperties.bVSync;
	}
}
