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
		virtual void SetClearColor() = 0;
		virtual void Clear() = 0;
		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) = 0;

		inline static API GetAPI() { return sAPI; };

	private:
		static API sAPI;
	};
}
