#include "AvalonPch.h"
#include "WindowWin.h"
#include "Avalon/Core/Core.h"
#include "Avalon/Log/Log.h"
#include "Avalon/Event/ApplicationEvents.h"
#include "Avalon/Event/InputEvents/KeyboardEvents.h"
#include "Avalon/Event/InputEvents/MouseEvents.h"
#include "Platform/OpenGL/OpenGLContext.h"

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

		mGLFWWindow = glfwCreateWindow((int)properties.width, properties.height, properties.title.c_str(), nullptr, nullptr);

		mContext = std::make_unique<OpenGLContext>(mGLFWWindow);
		mContext->Init();

		glfwSetWindowUserPointer(mGLFWWindow, &mWindowProperties);
		SetGLFWCallbacks();
		SetVSync(true);
	}

	void Avalon::WindowWin::Shutdown()
	{
		glfwDestroyWindow(mGLFWWindow);
	}

	void Avalon::WindowWin::OnUpdate()
	{
		glfwPollEvents();
		mContext->SwapBuffers();
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
		glfwSetWindowSizeCallback(mGLFWWindow, [](GLFWwindow* window, int width, int height)
			{
				WindowProperties& props = *(WindowProperties*)glfwGetWindowUserPointer(window);
				props.width = width;
				props.height = height;

				WindowResizeEvent event(width, height);
				props.eventCallback(event);
			});

		glfwSetWindowCloseCallback(mGLFWWindow, [](GLFWwindow* window)
			{
				WindowProperties& props = *(WindowProperties*)glfwGetWindowUserPointer(window);
				WindowCloseEvent event;
				props.eventCallback(event);
			});

		glfwSetKeyCallback(mGLFWWindow, [](GLFWwindow* window, int key, int scancode, int action, int mods)
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

		glfwSetCharCallback(mGLFWWindow, [](GLFWwindow* window, unsigned int keycode)
			{
				WindowProperties& props = *(WindowProperties*)glfwGetWindowUserPointer(window);

				KeyTypedEvent event(keycode);
				props.eventCallback(event);
			});

		glfwSetMouseButtonCallback(mGLFWWindow, [](GLFWwindow* window, int button, int action, int mods)
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

		glfwSetScrollCallback(mGLFWWindow, [](GLFWwindow* window, double xOffset, double yOffset)
			{
				WindowProperties& props = *(WindowProperties*)glfwGetWindowUserPointer(window);

				MouseScrolledEvent event((float)xOffset, (float)yOffset);
				props.eventCallback(event);
			});

		glfwSetCursorPosCallback(mGLFWWindow, [](GLFWwindow* window, double xPos, double yPos)
			{
				WindowProperties& props = *(WindowProperties*)glfwGetWindowUserPointer(window);

				MouseMovedEvent event((float)xPos, (float)yPos);
				props.eventCallback(event);
			});
	}
}
