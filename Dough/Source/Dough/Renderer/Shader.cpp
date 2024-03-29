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
		case RendererAPI::API::None:
			return nullptr;
		case RendererAPI::API::OpenGL:
			return new OpenGLShader(vertSource, fragSource);
		}

		DH_ASSERT_ERROR(false, "Tried to create shader for invalid RenderAPI (%s, id: %i)!", RendererAPI::GetAPIString(Renderer::GetAPI()), Renderer::GetAPI());
		return nullptr;
	}
}
