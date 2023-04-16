#pragma once

#include "Avalon/Event/Event.h"

namespace Avalon
{
	class TickEvent : public Event
	{
	public:
		TickEvent() {}

		EVENT_CLASS_TYPE(Tick)
		EVENT_CLASS_CATEGORY(GameLoop)
	};

	class UpdateEvent : public Event
	{
	public:
		UpdateEvent() {}

		EVENT_CLASS_TYPE(Update)
		EVENT_CLASS_CATEGORY(GameLoop)
	};

	class RenderEvent : public Event
	{
	public:
		RenderEvent() {}

		EVENT_CLASS_TYPE(Render)
		EVENT_CLASS_CATEGORY(GameLoop)
	};
}