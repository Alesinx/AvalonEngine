#pragma once

#include "Avalon/Event/Event.h"

namespace Avalon
{
	class WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(unsigned int width, unsigned int height) : 
			mWidth(width), mHeight(height) 
		{}

		EVENT_CLASS_TYPE(WindowResize)
		EVENT_CLASS_CATEGORY(Application)

		inline unsigned int GetWidth() const { return mWidth; }
		inline unsigned int GetHeight() const { return mHeight; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowResizeEvent: " << mWidth << ", " << mHeight;
			return ss.str();
		}

	private:
		unsigned int mWidth;
		unsigned int mHeight;
	};

	class WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent() {}

		EVENT_CLASS_TYPE(WindowClose)
		EVENT_CLASS_CATEGORY(Application)
	};
}
