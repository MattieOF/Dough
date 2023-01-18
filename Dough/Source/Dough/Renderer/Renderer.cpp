#include "dhpch.h"
#include "Dough/Renderer/Renderer.h"

namespace Dough
{
	RendererAPI Renderer::s_RenderAPI = RendererAPI::OpenGL;

	const char* Renderer::APIToString(RendererAPI API)
	{
		switch (API)
		{
		case RendererAPI::None:
			return "None";
		case RendererAPI::OpenGL:
			return "OpenGL";
		default:
			DH_ENGINE_ERROR("Renderer::APIToString called with invalid API {0}!", (int) API);
			return "Invalid";
		}
	}
}
