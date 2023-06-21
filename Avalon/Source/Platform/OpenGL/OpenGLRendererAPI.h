#pragma once

#include "Avalon/Renderer/RendererAPI.h"

namespace Avalon
{
	class OpenGLRendererAPI : public RendererAPI
	{
	public:
		virtual void Initialize() override;

		virtual void SetClearColor();
		virtual void Clear();
		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray);
	};
}
