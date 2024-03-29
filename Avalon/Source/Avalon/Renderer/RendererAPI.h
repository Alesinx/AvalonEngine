#pragma once

#include "Avalon/Renderer/VertexArray.h"

namespace Avalon
{
	class RendererAPI
	{
	public:
		enum class API
		{
			None = 0,
			OpenGL = 1
		};

	public:
		virtual ~RendererAPI() = default;

		virtual void Initialize() = 0;
		virtual void SetClearColor() = 0;
		virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;
		virtual void Clear() = 0;
		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) = 0;

		inline static API GetAPI() { return sAPI; };

	private:
		static API sAPI;
	};
}
