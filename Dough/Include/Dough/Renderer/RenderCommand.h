#pragma once

#include "RendererAPI.h"
#include "VertexArray.h"

namespace Dough
{
	class RenderCommand
	{
	public:
		FORCEINLINE static void SetClearColor(const glm::vec4& newClearColor)
		{
			s_RendererAPI->SetClearColor(newClearColor);
		}

		FORCEINLINE static void Clear()
		{
			s_RendererAPI->Clear();
		}

		FORCEINLINE static void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray)
		{
			s_RendererAPI->DrawIndexed(vertexArray);
		}

		FORCEINLINE static void SetViewport(const glm::vec2& newViewport)
		{
			s_RendererAPI->SetViewport(newViewport);
		}

	private:
		static RendererAPI* s_RendererAPI;
	};	
}
