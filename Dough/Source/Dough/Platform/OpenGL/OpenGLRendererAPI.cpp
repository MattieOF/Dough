#include "dhpch.h"
#include "Dough/Platform/OpenGL/OpenGLRendererAPI.h"

#include <glad/gl.h>

namespace Dough
{
	void OpenGLRendererAPI::SetClearColor(const glm::vec4& newClearColor)
	{
		glClearColor(newClearColor.r, newClearColor.b, newClearColor.b, newClearColor.a);
	}

	void OpenGLRendererAPI::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLRendererAPI::SetViewport(const glm::vec2& newViewport)
	{
		glViewport(0, 0, newViewport.x, newViewport.y);
	}

	void OpenGLRendererAPI::DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray)
	{
		glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
	}
}
