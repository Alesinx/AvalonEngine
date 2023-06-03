#pragma once

#include "Avalon/Renderer/Buffer.h"

namespace Avalon
{
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(const float* const vertices, const uint32_t size);
		virtual ~OpenGLVertexBuffer();

		virtual void Bind() const;
		virtual void Unbind() const;

		virtual const BufferLayout& GetLayout() const override { return mLayout; }
		virtual void SetLayout(const BufferLayout layout) override 
		{ 
			mLayout = layout; 
		}

	private:
		uint32_t mRendererId;
		BufferLayout mLayout;
	};

	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(const uint32_t* const indices, const uint32_t count);
		virtual ~OpenGLIndexBuffer();

		virtual void Bind() const;
		virtual void Unbind() const;

		virtual uint32_t GetCount() const { return  mCount; }

	private:
		uint32_t mRendererId;
		uint32_t mCount;
	};
}

