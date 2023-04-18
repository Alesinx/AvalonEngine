#include "AvalonPch.h"
#include "Window_Win.h"
#include "Avalon/Core.h"
#include "Avalon/Log/Log.h"
#include <glad/glad.h>

namespace Avalon
{
	static bool s_GLFWInitialized = false;

	Window* Window::Create(const WindowProperties& properties)
	{
		return new Window_Win(properties);
	}

	Avalon::Window_Win::Window_Win(const WindowProperties& properties)
	{
		Init(properties);
	}

	Avalon::Window_Win::~Window_Win()
	{
		Shutdown();
	}

	void Avalon::Window_Win::Init(const WindowProperties& properties)
	{
		AVALON_CORE_INFO("Creating window {0} ({1}, {2})", properties.title, properties.width, properties.height);

		if (!s_GLFWInitialized)
		{
			int success = glfwInit();
			AVALON_CORE_ASSERT(success, "Could not initialize GLFW");

			s_GLFWInitialized = true;
		}

		m_window = glfwCreateWindow((int)properties.width, properties.height, properties.title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_window);

		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		AVALON_CORE_ASSERT(status, "Failed to initialize Glad");

		glfwSetWindowUserPointer(m_window, &m_windowProperties);
		
	}

	void Avalon::Window_Win::Shutdown()
	{
		glfwDestroyWindow(m_window);
	}

	void Avalon::Window_Win::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_window);
	}

	unsigned int Avalon::Window_Win::GetWidth() const
	{
		return m_windowProperties.width;
	}

	unsigned int Avalon::Window_Win::GetHeight() const
	{
		return m_windowProperties.height;
	}

	void Window_Win::SetVSync(bool enabled)
	{
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		m_windowProperties.bVSync = enabled;
	}

	bool Window_Win::IsVSyncEnabled() const
	{
		return m_windowProperties.bVSync;
	}
}
