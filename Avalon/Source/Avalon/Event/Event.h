#pragma once

#include "AvalonPch.h"
#include "Avalon/Core/Core.h"

namespace Avalon
{
	enum class EventType
	{
		EventCategory_None = 0,

		EventType_WindowClose,
		EventType_WindowResize,
		EventType_WindowFocus,
		EventType_LostFocus,
		EventType_WindowMoved,

		EventType_Tick,
		EventType_Update,
		EventType_Render,

		EventType_KeyPressed,
		EventType_KeyReleased,
		EventType_KeyTyped,

		EventType_MouseButtonPressed,
		EventType_MouseButtonReleased,
		EventType_MouseMoved,
		EventType_MouseScrolled
	};

	enum EventCategory
	{
		EventCategory_None = 0,
		EventCategory_Application = BIT(0),
		EventCateogry_Input = BIT(1),
		EventCategory_Gameloop = BIT(2)
	};

#define EVENT_CLASS_TYPE(type) \
	static EventType GetStaticType() { return EventType::type; } \
	virtual EventType GetEventType() const override { return GetStaticType(); } \
	virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) \
	virtual int GetCategoryFlags() const override { return category; }

	class Event
	{
	public:
		bool Handled = false;

	public:
		virtual ~Event() = default;

		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); }

		inline bool IsInCategory(EventCategory category) { return GetCategoryFlags() & category; }

		template<typename T>
		bool Dispatch(std::function<bool(T&)> func)
		{
			if (GetEventType() == T::GetStaticType())
			{
				Handled = func(*(T*)this);
				return true;
			}
			return false;
		}
	};

	inline std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return os << e.ToString();
	}
}
