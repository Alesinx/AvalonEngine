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
		ImguiOverlay() {}
		virtual ~ImguiOverlay() {}

		void Initialize();
		void Render();
		void OnEvent(Event& event);

	public:
		static ImGuiKey ImGui_ImplGlfw_KeyToImGuiKey(int key);

	private:
		bool OnWindowResizeEvent(WindowResizeEvent& e);
		bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
		bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
		bool OnMouseMovedEvent(MouseMovedEvent& e);
		bool OnMouseScrolledEvent(MouseScrolledEvent& e);
		bool OnKeyPressedEvent(KeyPressedEvent& e);
		bool OnKeyReleasedEvent(KeyReleasedEvent& e);
		bool OnKeyTypedEvent(KeyTypedEvent& e);

	private:
		float mTime = 0.f;
	};	
}

