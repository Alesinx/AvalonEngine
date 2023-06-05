#include "AvalonPch.h"
#include "VertexArray.h"

#include "Avalon/Renderer/Renderer.h"
#include "Avalon/Renderer/RendererAPI.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Avalon
{
	VertexArray* VertexArray::Create()
	{
		switch(Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			AVALON_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return new OpenGLVertexArray();
		}
	}
}
