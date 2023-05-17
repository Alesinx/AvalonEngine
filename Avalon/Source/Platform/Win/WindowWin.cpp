#include "AvalonPch.h"
#include "WindowWin.h"
#include "Avalon/Core.h"
#include "Avalon/Log/Log.h"
#include "Avalon/Event/ApplicationEvents.h"
#include "Avalon/Event/InputEvents/KeyboardEvents.h"
#include "Avalon/Event/InputEvents/MouseEvents.h"

#include <glad/glad.h>

namespace Avalon
{
	static bool sGLFWInitialized = false;

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

		if (!sGLFWInitialized)
		{
			int success = glfwInit();
			AVALON_CORE_ASSERT(success, "Could not initialize GLFW");

			sGLFWInitialized = true;
		}

		mWindow = glfwCreateWindow((int)properties.width, properties.height, properties.title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(mWindow);

		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		AVALON_CORE_ASSERT(status, "Failed to initialize Glad");

		glfwSetWindowUserPointer(mWindow, &mWindowProperties);
		SetGLFWCallbacks();
		SetVSync(true);
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

	void WindowWin::SetVSync(bool enabled)
	{
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		mWindowProperties.bVSync = enabled;
	}

	void WindowWin::SetGLFWCallbacks()
	{
		glfwSetWindowSizeCallback(mWindow, [](GLFWwindow* window, int width, int height)
			{
				WindowProperties& props = *(WindowProperties*)glfwGetWindowUserPointer(window);
				props.width = width;
				props.height = height;

				WindowResizeEvent event(width, height);
				props.eventCallback(event);
			});

		glfwSetWindowCloseCallback(mWindow, [](GLFWwindow* window)
			{
				WindowProperties& props = *(WindowProperties*)glfwGetWindowUserPointer(window);
				WindowCloseEvent event;
				props.eventCallback(event);
			});

		glfwSetKeyCallback(mWindow, [](GLFWwindow* window, int key, int scancode, int action, int mods)
			{
				WindowProperties& props = *(WindowProperties*)glfwGetWindowUserPointer(window);

				switch (action)
				{
				case GLFW_PRESS:
				{
					KeyPressedEvent event(key, 0);
					props.eventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent event(key);
					props.eventCallback(event);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressedEvent event(key, 1);
					props.eventCallback(event);
					break;
				}
				}
			});

		glfwSetCharCallback(mWindow, [](GLFWwindow* window, unsigned int keycode)
			{
				WindowProperties& props = *(WindowProperties*)glfwGetWindowUserPointer(window);

				KeyTypedEvent event(keycode);
				props.eventCallback(event);
			});

		glfwSetMouseButtonCallback(mWindow, [](GLFWwindow* window, int button, int action, int mods)
			{
				WindowProperties& props = *(WindowProperties*)glfwGetWindowUserPointer(window);

				switch (action)
				{
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent event(button);
					props.eventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent event(button);
					props.eventCallback(event);
					break;
				}
				}
			});

		glfwSetScrollCallback(mWindow, [](GLFWwindow* window, double xOffset, double yOffset)
			{
				WindowProperties& props = *(WindowProperties*)glfwGetWindowUserPointer(window);

				MouseScrolledEvent event((float)xOffset, (float)yOffset);
				props.eventCallback(event);
			});

		glfwSetCursorPosCallback(mWindow, [](GLFWwindow* window, double xPos, double yPos)
			{
				WindowProperties& props = *(WindowProperties*)glfwGetWindowUserPointer(window);

				MouseMovedEvent event((float)xPos, (float)yPos);
				props.eventCallback(event);
			});
	}
}
