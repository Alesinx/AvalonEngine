#pragma once

#include "Avalon/Event/Event.h"

namespace Avalon
{
	class KeyEvent : public Event
	{
	public:
		EVENT_CLASS_CATEGORY(EventCateogry_Input)

		inline int GetKeyCode() const { return mKeyCode; }

	protected:
		KeyEvent(int keycode) : mKeyCode(keycode) 
		{}

		int mKeyCode;
	};

	class KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(int keycode, int repeatCount) : KeyEvent(keycode), mRepeatCount(repeatCount)
		{}

		EVENT_CLASS_TYPE(EventType_KeyPressed)

		inline int GetRepeatCount() const { return mRepeatCount; }

		std::string ToString() const 
		{
			std::stringstream ss;
			ss << "KeyPressed Event: " << mKeyCode << " (" << mRepeatCount << " repeats)";
			return ss.str();
		}

	private:
		int mRepeatCount;
	};

	class KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(int keycode) : KeyEvent(keycode)
		{}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyRelease Event: " << mKeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(EventType_KeyReleased)
	};

	class KeyTypedEvent : public KeyEvent
	{
	public:
		KeyTypedEvent(int keycode) : KeyEvent(keycode)
		{}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyTyped Event: " << mKeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(EventType_KeyTyped)
	};
}
