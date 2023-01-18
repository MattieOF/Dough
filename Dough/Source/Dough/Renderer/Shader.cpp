#include "dhpch.h"

#include "Dough/Renderer/Shader.h"
#include "Dough/Renderer/Renderer.h"

// Platform specific
#include "Dough/Platform/OpenGL/OpenGLShader.h"

namespace Dough
{
	Shader* Shader::Create(const std::string& vertSource, const std::string& fragSource)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None:
			return nullptr;
		case RendererAPI::OpenGL:
			return new OpenGLShader(vertSource, fragSource);
		}

		DH_ASSERT_ERROR(false, "Tried to create shader with invalid RenderAPI {0}.", Renderer::GetAPI());
		return nullptr;
	}
}
