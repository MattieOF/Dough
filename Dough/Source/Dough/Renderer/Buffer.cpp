#include "dhpch.h"
#include "Dough/Renderer/Buffer.h"
#include "Dough/Renderer/Renderer.h"

// Platform specific
#include "Dough/Platform/OpenGL/OpenGLBuffer.h"

namespace Dough
{
	// ------------------------
	// Static utility functions
	// ------------------------
	uint16_t GetShaderDataTypeSize(ShaderDataType type)
	{
		switch (type)
		{
			case ShaderDataType::None:   return 0;
			case ShaderDataType::Float:  return sizeof(float);
			case ShaderDataType::Float2: return sizeof(float) * 2;
			case ShaderDataType::Float3: return sizeof(float) * 3;
			case ShaderDataType::Float4: return sizeof(float) * 4;
			case ShaderDataType::Mat3:   return sizeof(float) * 3 * 3;
			case ShaderDataType::Mat4:   return sizeof(float) * 4 * 4;
			case ShaderDataType::Int:    return sizeof(int);
			case ShaderDataType::Int2:   return sizeof(int) * 2;
			case ShaderDataType::Int3:   return sizeof(int) * 3;
			case ShaderDataType::Int4:   return sizeof(int) * 4;
			case ShaderDataType::Bool:   return sizeof(bool);
		}

		DH_ASSERT_ERROR(false, "Unknown shader data type! (id: %i)", (int) type);
		return 0;
	}

	uint16_t GetShaderDataTypeElementCount(ShaderDataType type)
	{
		switch (type)
		{
			case ShaderDataType::None:   return 0;
			case ShaderDataType::Float:  return 1;
			case ShaderDataType::Float2: return 2;
			case ShaderDataType::Float3: return 3;
			case ShaderDataType::Float4: return 4;
			case ShaderDataType::Mat3:   return 3 * 3;
			case ShaderDataType::Mat4:   return 4 * 4;
			case ShaderDataType::Int:    return 1;
			case ShaderDataType::Int2:   return 2;
			case ShaderDataType::Int3:   return 3;
			case ShaderDataType::Int4:   return 4;
			case ShaderDataType::Bool:   return 1;
		}

		DH_ASSERT_ERROR(false, "Unknown shader data type! (id: %i)", (int)type);
		return 0;
	}

	// ------------------------
	// Vertex buffer
	// ------------------------
	VertexBuffer* VertexBuffer::Create(float* verticies, const int count)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None:
			return nullptr;
		case RendererAPI::OpenGL:
			return new OpenGLVertexBuffer(verticies, count);
		}

		DH_ASSERT_ERROR(false, "Tried to create vertex buffer for invalid RenderAPI (%s, id: %i)!", Renderer::APIToString(Renderer::GetAPI()), Renderer::GetAPI());
		return nullptr;
	}

	// ------------------------
	// Index buffer
	// ------------------------
	IndexBuffer* IndexBuffer::Create(uint32_t* indicies, const int count)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None:
			return nullptr;
		case RendererAPI::OpenGL:
			return new OpenGLIndexBuffer(indicies, count);
		}

		DH_ASSERT_ERROR(false, "Tried to create index buffer for invalid RenderAPI (%s, id: %i)!", Renderer::APIToString(Renderer::GetAPI()), Renderer::GetAPI());
		return nullptr;
	}

	// ------------------------
	// Buffer layout
	// ------------------------
	void BufferLayout::CalculateOffsetsAndStride()
	{
		uint16_t totalSize = 0;

		for (auto& element : m_Elements)
		{
			element.Offset = totalSize;
			totalSize += element.Size;
		}

		m_Stride = totalSize;
	}
}
