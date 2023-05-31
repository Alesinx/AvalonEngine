#pragma once

namespace Avalon
{
	enum class RendererAPI
	{
		None = 0,
		OpenGL = 1
	};

	class Renderer
	{
	public:
		inline static RendererAPI GetAPI() { return sRendererAPI; }

	private:
		static RendererAPI sRendererAPI;
	};
}
