#include "AvalonPch.h"
#include "Avalon/Renderer/RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Avalon
{
	RendererAPI* RenderCommand::sRendererAPI = new OpenGLRendererAPI;
}
