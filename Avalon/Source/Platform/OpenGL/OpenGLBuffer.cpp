#include "AvalonPch.h"
#include "OpenGLBuffer.h"

#include <glad/glad.h>

namespace Avalon
{
/////////////////////////////////////////////////////////////////////////////
// VertexBuffer /////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

	OpenGLVertexBuffer::OpenGLVertexBuffer(const float* const vertices, const uint32_t size)
	{
		glCreateBuffers(1, &mRendererId);
		glBindBuffer(GL_ARRAY_BUFFER, mRendererId);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		glDeleteBuffers(1, &mRendererId);
	}

	void OpenGLVertexBuffer::Bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, mRendererId);
	}

	void OpenGLVertexBuffer::Unbind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

/////////////////////////////////////////////////////////////////////////////
// IndexBuffer //////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

	OpenGLIndexBuffer::OpenGLIndexBuffer(const uint32_t* const indices, const uint32_t count) : 
		mCount(count)
	{
		glCreateBuffers(1, &mRendererId);
		glBindBuffer(GL_ARRAY_BUFFER, mRendererId);
		glBufferData(GL_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		glDeleteBuffers(1, &mRendererId);
	}

	void OpenGLIndexBuffer::Bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mRendererId);
	}

	void OpenGLIndexBuffer::Unbind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}
