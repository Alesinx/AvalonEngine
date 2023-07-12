#pragma once

#include "AvalonPch.h"
#include "Avalon/Core/Core.h"
#include "Avalon/Event/Event.h"

namespace Avalon
{
	struct WindowProperties
	{
		std::string title = "Avalon";
		uint32_t width = 1280;
		uint32_t height = 720;
		bool bVSync = false;
		std::function<void(Event&)> eventCallback;

		WindowProperties(const std::string& title = "Avalon", uint32_t width = 1280, uint32_t height = 720, bool bVSync = false) :
			title(title), width(width), height(height), bVSync(bVSync)
		{}
	};

	class Window
	{
	public:
		virtual ~Window() = default;

		virtual void OnUpdate() = 0;

		virtual void* GetNativeWindow() const = 0;
		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;

		virtual inline void SetEventCallback(const std::function<void(Event&)>& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSyncEnabled() const = 0;

		static std::unique_ptr<Window> Create(const WindowProperties& props = WindowProperties());
	};
}
