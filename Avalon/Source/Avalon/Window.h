#pragma once

#include "AvalonPch.h"
#include "Avalon/Core.h"

namespace Avalon
{
	struct WindowProperties
	{
		std::string title;
		unsigned int width;
		unsigned int height;

		WindowProperties(const std::string& title = "Avalon", unsigned int width = 1280, unsigned int height = 720) :
			title(title), width(width), height(height)
		{}
	};

	class Window
	{
	public:
		virtual ~Window() {};

		virtual void* GetNativeWindow() const = 0;
		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		virtual void OnUpdate() = 0;

		static Window* Create(const WindowProperties& props = WindowProperties());
	};
}
