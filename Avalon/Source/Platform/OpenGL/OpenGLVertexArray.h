#pragma once

#include "Avalon/Renderer/VertexArray.h"

namespace Avalon
{
	class OpenGLVertexArray : public VertexArray
	{
	public:
		OpenGLVertexArray();
		virtual ~OpenGLVertexArray();

		virtual void Bind() const;
		virtual void Unbind() const;
		virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer);
		virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer);
		virtual const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffer() const { return mVertexBuffers; }
		virtual const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const { return mIndexBuffer; }

	private:
		uint32_t mRendererId;
		std::vector<std::shared_ptr<VertexBuffer>> mVertexBuffers;
		std::shared_ptr<IndexBuffer> mIndexBuffer;
	};
}
