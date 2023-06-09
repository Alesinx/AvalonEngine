#include "AvalonPch.h"
#include "Shader.h"

#include "Avalon/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Avalon
{
	Shader* Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None : 
			AVALON_CORE_ASSERT(false, "RendererAPI::None is currently not supported"); 
			return nullptr;
		case RendererAPI::API::OpenGL :
			return new OpenGLShader(vertexSrc, fragmentSrc);
		}

		AVALON_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}
}