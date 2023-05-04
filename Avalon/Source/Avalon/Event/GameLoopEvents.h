#pragma once

#include "Avalon/Event/Event.h"

namespace Avalon
{
	class TickEvent : public Event
	{
	public:
		TickEvent() {}

		EVENT_CLASS_TYPE(EventType_Tick)
		EVENT_CLASS_CATEGORY(EventCategory_Gameloop)
	};

	class UpdateEvent : public Event
	{
	public:
		UpdateEvent() {}

		EVENT_CLASS_TYPE(EventType_Update)
		EVENT_CLASS_CATEGORY(EventCategory_Gameloop)
	};

	class RenderEvent : public Event
	{
	public:
		RenderEvent() {}

		EVENT_CLASS_TYPE(EventType_Render)
		EVENT_CLASS_CATEGORY(EventCategory_Gameloop)
	};
}