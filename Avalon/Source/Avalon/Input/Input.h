#pragma once

#include "Avalon/Core/Core.h"

namespace Avalon
{
	class Input
	{
	public:
		static Vec2 GetMousePosition();
		static bool IsMouseButtonPressed(int button);
		static bool IsKeyPressed(int keycode);
		static float GetMouseX();
		static float GetMouseY();
	};
}
