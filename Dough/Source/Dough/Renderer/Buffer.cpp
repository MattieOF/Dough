#include "dhpch.h"
#include "Dough/Renderer/Buffer.h"
#include "Dough/Renderer/Renderer.h"

#include "Dough/Platform/OpenGL/OpenGLBuffer.h"

namespace Dough
{
	VertexBuffer* VertexBuffer::Create(float* verticies, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None:
			return nullptr;
		case RendererAPI::OpenGL:
			return new OpenGLVertexBuffer(verticies, size);
		}

		DH_ASSERT_ERROR(false, "Tried to create VertexBuffer with invalid RenderAPI {0}.", Renderer::GetAPI());
		return nullptr;
	}

	IndexBuffer* IndexBuffer::Create(uint32_t* indicies, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None:
			return nullptr;
		case RendererAPI::OpenGL:
			return new OpenGLIndexBuffer(indicies, size);
		}

		DH_ASSERT_ERROR(false, "Tried to create IndexBuffer with invalid RenderAPI {0}.", Renderer::GetAPI());
		return nullptr;
	}
}
