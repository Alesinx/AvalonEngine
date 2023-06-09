#include "AvalonPch.h"
#include "Texture.h"

#include "Avalon/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"

namespace Avalon
{
	Texture2D* Texture2D::Create(const std::string& path)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    AVALON_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return new OpenGLTexture2D(path);
		}

		AVALON_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}
