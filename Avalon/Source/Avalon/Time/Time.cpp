#include "AvalonPch.h"
#include "Avalon/Time/Time.h"
#include <glfw/glfw3.h>

namespace Avalon
{
	float Time::GetCurrentTime()
	{
		return (float)glfwGetTime();
	}
}
