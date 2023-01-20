#include "dhpch.h"
#include "Dough/Renderer/RenderCommand.h"

#include "Dough/Platform/OpenGL/OpenGLRendererAPI.h"

namespace Dough
{
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI();
}
