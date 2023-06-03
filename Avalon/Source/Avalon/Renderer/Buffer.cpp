#include "AvalonPch.h"
#include "Buffer.h"
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

	IndexBuffer* IndexBuffer::Create(const uint32_t* const indices, const uint32_t count)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None:
			AVALON_CORE_ASSERT(false, "RendererAPI::None is currently not supported")
				return nullptr;
		case RendererAPI::OpenGL:
			return new OpenGLIndexBuffer(indices, count);
		}

		AVALON_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}

	void BufferLayout::CalculateOffsetAndStride()
	{
		uint32_t offset = 0;
		for (BufferElement& element : mElements)
		{
			element.offset = offset;
			offset += element.size;
		}
		mStride = offset;
	}

	uint32_t BufferElement::GetComponentCount() const
	{
		switch (type)
		{
		case ShaderDataType::Float:
			return 4;
		case ShaderDataType::Float2:
			return 2;
		case ShaderDataType::Float3:
			return 3;
		case ShaderDataType::Float4:
			return 4;
		case ShaderDataType::Mat3:
			return 3 * 3;
		case ShaderDataType::Mat4:
			return 4 * 4;
		case ShaderDataType::Int:
			return 1;
		case ShaderDataType::Int2:
			return 2;
		case ShaderDataType::Int3:
			return 3;
		case ShaderDataType::Int4:
			return 4;
		case ShaderDataType::Bool:
			return 1;
		}

		AVALON_CORE_ASSERT(false, "Unknown ShaderDataType");
		return 0;
	}
}
