#pragma once

#include "Avalon/Core/Core.h"

namespace Avalon
{
	class Input
	{
	public:
		static std::pair<float, float> GetMousePosition();
		static bool IsMouseButtonPressed(int button);
		static bool IsKeyPressed(int keycode);
		static float GetMouseX();
		static float GetMouseY();
	};
}
