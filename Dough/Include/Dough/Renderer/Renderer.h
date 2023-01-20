#pragma once

#include "RendererAPI.h"

namespace Dough
{
	class Renderer
	{
	public:
		static void BeginScene(); // TODO: Scene params
		static void EndScene();

		static void Submit(const std::shared_ptr<VertexArray>& vertexArray);

		FORCEINLINE static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	};
}
