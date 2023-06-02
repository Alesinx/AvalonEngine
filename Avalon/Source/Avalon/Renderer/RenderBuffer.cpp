#include "AvalonPch.h"
#include "RenderBuffer.h"
#include "Avalon/Renderer/Renderer.h"

#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Avalon
{
	VertexBuffer* VertexBuffer::Create(const float* const vertices, const uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None:
			AVALON_CORE_ASSERT(false, "RendererAPI::None is currently not supported") 
			return nullptr;
		case RendererAPI::OpenGL:
			return new OpenGLVertexBuffer(vertices, size);
		}

		AVALON_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}

	IndexBuffer* IndexBuffer::Create(const uint32_t* const indices, const uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None:
			AVALON_CORE_ASSERT(false, "RendererAPI::None is currently not supported")
				return nullptr;
		case RendererAPI::OpenGL:
			return new OpenGLIndexBuffer(indices, size);
		}

		AVALON_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}
}
