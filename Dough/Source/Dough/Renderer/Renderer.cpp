#include "dhpch.h"
#include "Dough/Renderer/Renderer.h"

#include "Dough/Renderer/RenderCommand.h"

namespace Dough
{
	void Renderer::BeginScene()
	{
	}

	void Renderer::EndScene()
	{
	}

	void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray)
	{
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
}
