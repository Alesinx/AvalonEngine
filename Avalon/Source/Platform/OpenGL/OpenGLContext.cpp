#include "AvalonPch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <GL/GL.h>

namespace Avalon
{
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle) : 
		mWindowHandle(windowHandle)
	{
		AVALON_CORE_ASSERT(windowHandle, "Window handle is null");
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(mWindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		AVALON_CORE_ASSERT(status, "Failed to initialize Glad");

		AVALON_CORE_INFO("OpenGL Info:");
		AVALON_CORE_INFO(" - Vendor: {0}", (const char*)glGetString(GL_VENDOR));
		AVALON_CORE_INFO(" - Renderer: {0}", (const char*)glGetString(GL_RENDERER));
		AVALON_CORE_INFO(" - Version: {0}", (const char*)glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(mWindowHandle);
	}
}