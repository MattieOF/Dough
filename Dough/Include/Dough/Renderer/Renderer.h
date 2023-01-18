#pragma once

#include "Buffer.h"
#include "GraphicsContext.h"
#include "Shader.h"

namespace Dough
{
	enum class RendererAPI
	{
		None = 0,
		OpenGL = 1
	};

	class Renderer
	{
	public:
		inline static RendererAPI GetAPI() { return s_RenderAPI; }
		static const char* APIToString(RendererAPI API);
	private:
		static RendererAPI s_RenderAPI;
	};
}
