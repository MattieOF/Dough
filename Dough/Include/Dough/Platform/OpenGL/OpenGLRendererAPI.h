#pragma once
#include "Dough/Renderer/RendererAPI.h"

namespace Dough
{
	class OpenGLRendererAPI : public RendererAPI
	{
		void SetClearColor(const glm::vec4& newClearColor) override;
		void Clear() override;

		void SetViewport(const glm::vec2& newViewport) override;

		void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) override;
	};
}
