#pragma once

#include <glm/glm.hpp>

#include "VertexArray.h"
#include <Dough/Core/Core.h>

namespace Dough
{
	class RendererAPI
	{
	public:
		enum class API
		{
			None = 0,
			OpenGL = 1
		};

		FORCEINLINE static API GetAPI() { return s_API; }
		static const char* GetAPIString(API api);

		virtual void SetClearColor(const glm::vec4& newClearColor) = 0;
		virtual void Clear() = 0;
		virtual void SetViewport(const glm::vec2& newViewport) = 0;

		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) = 0;

	private:
		static API s_API;
	};
}
