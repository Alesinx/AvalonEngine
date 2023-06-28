#pragma once

#include "Avalon/Core/Core.h"

namespace Avalon
{
	class Input
	{
	public:
		inline static std::pair<float, float> GetMousePosition() { return sInstance->GetMousePositionImpl(); }
		inline static bool IsMouseButtonPressed(int button) { return sInstance->IsMouseButtonPressedImpl(button); }
		inline static bool IsKeyPressed(int keycode) { return sInstance->IsKeyPressedImpl(keycode); }
		inline static float GetMouseX() { return sInstance->GetMouseXImpl(); }
		inline static float GetMouseY() { return sInstance->GetMouseYImpl(); }

	protected:
		Input(const Input&) = delete;
		Input& operator=(const Input&) = delete;
		Input() = default;

		virtual std::pair<float, float> GetMousePositionImpl() = 0;
		virtual bool IsMouseButtonPressedImpl(int button) = 0;
		virtual bool IsKeyPressedImpl(int keycode) = 0;
		virtual float GetMouseXImpl() = 0;
		virtual float GetMouseYImpl() = 0;

	private:
		static std::unique_ptr<Input> sInstance;
	};
}
