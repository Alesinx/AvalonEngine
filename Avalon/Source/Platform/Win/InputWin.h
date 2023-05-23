#pragma once

#include "Avalon/Input.h"

namespace Avalon
{
	class InputWin : public Input
	{
	protected:
		std::pair<float, float> GetMousePositionImpl() override;
		bool IsMouseButtonPressedImpl(int button) override;
		bool IsKeyPressedImpl(int keycode) override;
		float GetMouseXImpl() override;
		float GetMouseYImpl() override;
	};
}

