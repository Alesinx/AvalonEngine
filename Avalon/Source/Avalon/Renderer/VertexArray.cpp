#include "AvalonPch.h"
#include "VertexArray.h"

#include "Avalon/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Avalon
{
	VertexArray* VertexArray::Create()
	{
		switch(Renderer::GetAPI())
		{
		case RendererAPI::None:
			AVALON_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;
		case RendererAPI::OpenGL:
			return new OpenGLVertexArray();
		}
	}
}
