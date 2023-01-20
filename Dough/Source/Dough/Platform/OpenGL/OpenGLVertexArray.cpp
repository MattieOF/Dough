#include "dhpch.h"

#include <glad/gl.h>

#include "Dough/Platform/OpenGL/OpenGLVertexArray.h"

#include "Dough/Platform/OpenGL/OpenGLShader.h"

namespace Dough
{
	OpenGLVertexArray::OpenGLVertexArray()
		: m_RendererID(0)
	{
		glCreateVertexArrays(1, &m_RendererID);
	}

	void OpenGLVertexArray::Bind() const
	{
		glBindVertexArray(m_RendererID);
	}

	void OpenGLVertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& buffer)
	{
		// First, check that the buffer is valid
		DH_ASSERT_ERROR(!buffer->GetLayout().GetElements().empty(), "Vertex buffer provided in OpenGLVertexArray::AddVertexBuffer has no layout! (elements array is empty)");

		// It is, so bind the VA
		glBindVertexArray(m_RendererID);

		// Then bind the buffer to the VA
		buffer->Bind();

		// Set up buffer layout
		const auto& layout = buffer->GetLayout();
		int elementIndex = 0;
		for (auto& element : layout)
		{
			glEnableVertexAttribArray(elementIndex);
			glVertexAttribPointer(elementIndex, GetShaderDataTypeElementCount(element.Type),
			                      ShaderDataTypeToGLBaseType(element.Type), element.Normalised ? GL_TRUE : GL_FALSE,
			                      layout.GetStride(),
			                      reinterpret_cast<const void*>(element.Offset));
			elementIndex++;
		}

		// Finally, add the buffer to the list
		m_VertexBuffers.push_back(buffer);
	}

	void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& buffer)
	{
		// First, bind the VA
		glBindVertexArray(m_RendererID);

		// Then bind the buffer to the VA
		buffer->Bind();

		// Finally, set the index buffer variable
		m_IndexBuffer = buffer;
	}
}
