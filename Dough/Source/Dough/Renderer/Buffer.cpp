#include "dhpch.h"
#include "Dough/Renderer/Buffer.h"
#include "Dough/Renderer/Renderer.h"

#include "Dough/Platform/OpenGL/OpenGLBuffer.h"

namespace Dough
{
	VertexBuffer* VertexBuffer::Create(float* verticies, const int count)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None:
			return nullptr;
		case RendererAPI::OpenGL:
			return new OpenGLVertexBuffer(verticies, count);
		}

		DH_ASSERT_ERROR(false, "Tried to create VertexBuffer with invalid RenderAPI {0}.", Renderer::GetAPI());
		return nullptr;
	}

	IndexBuffer* IndexBuffer::Create(uint32_t* indicies, const int count)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None:
			return nullptr;
		case RendererAPI::OpenGL:
			return new OpenGLIndexBuffer(indicies, count);
		}

		DH_ASSERT_ERROR(false, "Tried to create IndexBuffer with invalid RenderAPI %i.", (int) Renderer::GetAPI());
		return nullptr;
	}
}
