#pragma once

namespace Avalon
{
	struct FramebufferSpecification
	{
		uint32_t Width;
		uint32_t Height;
		uint32_t Samples = 1;
	};

	class Framebuffer
	{
	public:

		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		virtual uint32_t GetColorAttachmentRendererID() const = 0;
		virtual const FramebufferSpecification& GetSpecification() const = 0;

		static std::shared_ptr<Framebuffer> Create(const FramebufferSpecification& spec);
	};
}
