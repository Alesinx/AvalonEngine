#include "AvalonPch.h"
#include "Avalon/Renderer/FrameBuffer.h"

#include "Avalon/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLFramebuffer.h"

namespace Avalon {

	std::shared_ptr<Framebuffer> Framebuffer::Create(const FramebufferSpecification& spec)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    AVALON_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return std::make_shared<OpenGLFramebuffer>(spec);
		}

		AVALON_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}
