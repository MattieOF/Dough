#include "dhpch.h"

#include "Dough/Renderer/RendererAPI.h"

namespace Dough
{
	RendererAPI::API RendererAPI::s_API = RendererAPI::API::OpenGL;

	const char* RendererAPI::GetAPIString(API api)
	{
		switch (api)
		{
		case API::None:
			return "None";
		case API::OpenGL:
			return "OpenGL";
		default:
			DH_ENGINE_ERROR("Renderer::APIToString called with invalid API {0}!", static_cast<int>(api));
			return "Invalid";
		}
	}
}
