#pragma once

#include "AvalonPch.h"
#include "Avalon/Core.h"

namespace Avalon
{
	enum class EventType
	{
		None = 0,

		WindowClose,
		WindowResize,
		WindowFocus,
		WindowLostFocus,
		WindowMoved,

		Tick,
		Update,
		Render,

		KeyPressed,
		KeyReleased,

		MouseButtonPressed,
		MouseButtonReleased,
		MouseMoved,
		MouseScrolled
	};

	enum EventCategory
	{
		None = 0,
		Application = BIT(0),
		Input = BIT(1),
		GameLoop = BIT(2)
	};

#define EVENT_CLASS_TYPE(type) \
	static EventType GetStaticType() { return EventType::##type; } \
	virtual EventType GetEventType() const override { return GetStaticType(); } \
	virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) \
	virtual int GetCategoryFlags() const override { return category; }

	class Event
	{
	public:
		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); }

		inline bool IsInCategory(EventCategory category)
		{
			return GetCategoryFlags() & category;
		}

	private:
		bool Handled = false;
	};

	inline std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return os << e.ToString();
	}

	static class EventDispatcher
	{
		template<typename T>
		using EventFn = std::function<bool(T&)>;

	public:
		template<typename T>
		static bool Dispatch(Event event, std::function<bool(T&)> Function)
		{
			if (event.GetEventType() == T::GetStaticType())
			{
				if (event.GetEventType() == T::GetStaticType())
				{
					event.Handled = Function(*(T*)&event);
					return true;
				}
				return false;
			}
		}
	};
}
