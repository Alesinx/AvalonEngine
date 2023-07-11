#pragma once

#include "Avalon/Renderer/FrameBuffer.h"

namespace Avalon
{
	class OpenGLFramebuffer : public Framebuffer
	{
	public:
	public:
		OpenGLFramebuffer(const FramebufferSpecification& spec);
		virtual ~OpenGLFramebuffer();

		void Invalidate();

		virtual void Bind() override;
		virtual void Unbind() override;

		virtual uint32_t GetColorAttachmentRendererID() const override { return mColorAttachment; }
		virtual const FramebufferSpecification& GetSpecification() const override { return mSpecification; }

	private:
		uint32_t mRendererID;
		uint32_t mColorAttachment;
		uint32_t mDepthAttachment;
		FramebufferSpecification mSpecification;
	};
}
