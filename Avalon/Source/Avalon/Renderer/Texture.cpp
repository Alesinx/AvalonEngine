#include "AvalonPch.h"
#include "Texture.h"

#include "Avalon/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"

namespace Avalon
{
	std::shared_ptr<Texture2D> Texture2D::Create(uint32_t width, uint32_t height)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    AVALON_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return std::make_shared<OpenGLTexture2D>(width, height);
		}

		AVALON_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	std::shared_ptr<Texture2D> Texture2D::Create(const std::string& path)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:    
				AVALON_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); 
				return nullptr;
			case RendererAPI::API::OpenGL:  
				return std::make_shared<OpenGLTexture2D>(path);
		}

		AVALON_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}
