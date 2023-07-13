#include "AvalonPch.h"
#include "Avalon/Input/Input.h"
#include "Avalon/Core/Application.h"

#include <GLFW/glfw3.h>

namespace Avalon
{
	Vec2 Input::GetMousePosition()
	{
		GLFWwindow* window = static_cast<GLFWwindow*>(Application::GetInstance().GetWindow().GetNativeWindow());
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);

		return { static_cast<float>(xpos), static_cast<float>(ypos) };
	}

	bool Input::IsMouseButtonPressed(int button)
	{
		GLFWwindow* window = static_cast<GLFWwindow*>(Application::GetInstance().GetWindow().GetNativeWindow());
		int state = glfwGetMouseButton(window, button);
		return state == GLFW_PRESS;
	}

	bool Input::IsKeyPressed(int keycode)
	{
		GLFWwindow* window = static_cast<GLFWwindow*>(Application::GetInstance().GetWindow().GetNativeWindow());
		int state = glfwGetKey(window, keycode);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	float Input::GetMouseX()
	{
		Vec2 mousePos = GetMousePosition();
		return mousePos.x;
	}

	float Input::GetMouseY()
	{
		Vec2 mousePos = GetMousePosition();
		return mousePos.y;
	}
}
