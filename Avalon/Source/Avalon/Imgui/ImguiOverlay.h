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
		bool showDemo = true;

	public:
		ImguiOverlay() = default;
		virtual ~ImguiOverlay() = default;

		void Initialize();
		void Begin();
		void Render();
		void End();

	private:
		float mTime = 0.f;
	};	
}

