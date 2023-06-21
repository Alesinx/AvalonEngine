#include "AvalonPch.h"
#include "OpenGLVertexArray.h"

#include <glad/glad.h>

namespace Avalon
{
	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
		case Avalon::ShaderDataType::Float:
			return GL_FLOAT;
		case Avalon::ShaderDataType::Float2:
			return GL_FLOAT;
		case Avalon::ShaderDataType::Float3:
			return GL_FLOAT;
		case Avalon::ShaderDataType::Float4:
			return GL_FLOAT;
		case Avalon::ShaderDataType::Mat3:
			return GL_FLOAT;
		case Avalon::ShaderDataType::Mat4:
			return GL_FLOAT;
		case Avalon::ShaderDataType::Int:
			return GL_INT;
		case Avalon::ShaderDataType::Int2:
			return GL_INT;
		case Avalon::ShaderDataType::Int3:
			return GL_INT;
		case Avalon::ShaderDataType::Int4:
			return GL_INT;
		case Avalon::ShaderDataType::Bool:
			return GL_BOOL;
		}

		AVALON_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	OpenGLVertexArray::OpenGLVertexArray()
	{
		glCreateVertexArrays(1, &mRendererId);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &mRendererId);
	}

	void OpenGLVertexArray::Bind() const
	{
		glBindVertexArray(mRendererId);
	}

	void OpenGLVertexArray::Unbind() const
	{
		glBindVertexArray(mRendererId);
	}

	void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
	{
		AVALON_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size() > 0, "Vertex buffer has no layout");

		glBindVertexArray(mRendererId);
		vertexBuffer->Bind();

		const BufferLayout layout = vertexBuffer->GetLayout();
		for (const BufferElement& element : layout)
		{
			glEnableVertexAttribArray(mVertexBufferIndex);
			glVertexAttribPointer(
				mVertexBufferIndex,
				element.GetComponentCount(),
				ShaderDataTypeToOpenGLBaseType(element.type),
				element.normalized ? GL_TRUE : GL_FALSE,
				layout.GetStride(),
				(const void*)element.offset);

			mVertexBufferIndex++;
		}

		mVertexBuffers.push_back(vertexBuffer);
	}

	void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
	{
		Bind();
		indexBuffer->Bind();

		mIndexBuffer = indexBuffer;
	}
}
