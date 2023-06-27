#pragma once

#include "Avalon/Event/ApplicationEvents.h"
#include "Avalon/Event/InputEvents/MouseEvents.h"
#include "Avalon/Event/InputEvents/KeyboardEvents.h"

enum ImGuiKey : int;

namespace Avalon
{
	class ImguiOverlay
	{
	public:

	public:
		ImguiOverlay() = default;
		virtual ~ImguiOverlay() = default;

		void Initialize();
		void Render();
		//void OnEvent(Event& event);

	private:
		float mTime = 0.f;
	};	
}

