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

		virtual void Resize(uint32_t width, uint32_t height) override;

		virtual uint32_t GetColorAttachmentRendererID() const override { return mColorAttachment; }
		virtual const FramebufferSpecification& GetSpecification() const override { return mSpecification; }

	private:
		uint32_t mRendererID = 0;
		uint32_t mColorAttachment = 0;
		uint32_t mDepthAttachment = 0;
		FramebufferSpecification mSpecification;
	};
}
