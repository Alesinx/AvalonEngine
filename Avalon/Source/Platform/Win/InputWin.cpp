#include "AvalonPch.h"
#include "Platform/Win/InputWin.h"
#include "Avalon/Core/Application.h"

#include <GLFW/glfw3.h>

namespace Avalon
{
	std::unique_ptr<Input> Input::sInstance = std::make_unique<InputWin>();

	std::pair<float, float> InputWin::GetMousePositionImpl()
	{
		GLFWwindow* window = static_cast<GLFWwindow*>(Application::GetInstance().GetWindow().GetNativeWindow());
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);

		return { static_cast<float>(xpos), static_cast<float>(ypos) };
	}

	bool InputWin::IsMouseButtonPressedImpl(int button)
	{
		GLFWwindow* window = static_cast<GLFWwindow*>(Application::GetInstance().GetWindow().GetNativeWindow());
		int state = glfwGetMouseButton(window, button);
		return state == GLFW_PRESS;
	}

	bool InputWin::IsKeyPressedImpl(int keycode)
	{
		GLFWwindow* window = static_cast<GLFWwindow*>(Application::GetInstance().GetWindow().GetNativeWindow());
		int state = glfwGetKey(window, keycode);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	float InputWin::GetMouseXImpl()
	{
		std::pair<float, float> mousePos = GetMousePositionImpl();
		return mousePos.first;
	}

	float InputWin::GetMouseYImpl()
	{
		std::pair<float, float> mousePos = GetMousePositionImpl();
		return mousePos.second;
	}
}
