#include "dhpch.h"

#include "Dough/Renderer/VertexArray.h"

#include "Dough/Platform/OpenGL/OpenGLVertexArray.h"
#include "Dough/Renderer/Renderer.h"

namespace Dough
{
	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:
				return nullptr;
			case RendererAPI::API::OpenGL:
				return new OpenGLVertexArray();
		}

		DH_ASSERT_ERROR(false, "Tried to create vertex array for invalid RenderAPI (%s, id: %i)!", RendererAPI::GetAPIString(Renderer::GetAPI()), Renderer::GetAPI());
		return nullptr;
	}
}
