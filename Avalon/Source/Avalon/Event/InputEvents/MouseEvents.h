#pragma once

#include "Avalon/Event/Event.h"

namespace Avalon
{
	class MouseMovedEvent : public Event
	{
	public:
		MouseMovedEvent(float x, float y) : mMouseX(x), mMouseY(y)
		{}

		EVENT_CLASS_TYPE(MouseMoved);
		EVENT_CLASS_CATEGORY(Input);

		inline float GetX() const { return mMouseX; }
		inline float GetY() const { return mMouseY; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseMoved Event: " << mMouseX << ", " << mMouseY;
			return ss.str();
		}

	private:
		float mMouseX;
		float mMouseY;
	};

	class MouseScrolledEvent : public Event
	{
	public:
		MouseScrolledEvent(float xOffset, float yOffset) : mXOffset(xOffset), mYOffset(yOffset)
		{}

		EVENT_CLASS_TYPE(MouseScrolled);
		EVENT_CLASS_CATEGORY(Input);

		inline float GetXOffset() const { return mXOffset; }
		inline float GetYOffset() const { return mYOffset; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseScrolled Event: " << mXOffset << ", " << mYOffset;
			return ss.str();
		}

	private:
		float mXOffset;
		float mYOffset;
	};

	class MouseButtonEvent : public Event
	{
	public:
		EVENT_CLASS_CATEGORY(Input)

			inline int GetMouseButton() const { return mButton; }

	protected:
		MouseButtonEvent(int button) : mButton(button)
		{}

		int mButton;
	};

	class MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(int button)
			: MouseButtonEvent(button)
		{}

		EVENT_CLASS_TYPE(MouseButtonPressed)

			std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonPressed Event: " << mButton;
			return ss.str();
		}
	};

	class MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent(int button) : MouseButtonEvent(button)
		{}

		EVENT_CLASS_TYPE(MouseButtonReleased)

			std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonReleased Event: " << mButton;
			return ss.str();
		}
	};
}