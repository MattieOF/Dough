#pragma once

#include "Dough/Renderer/Buffer.h"

namespace Dough
{
	class OpenGLVertexBuffer final : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(float* verticies, int count);
		~OpenGLVertexBuffer() override;

		void Bind() const override;
		void Unbind() const override;

		[[nodiscard]] FORCEINLINE int GetCount() const override { return m_Count; }
	private:
		int m_Count;
		uint32_t m_RendererID = 0;
	};

	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(uint32_t* indicies, int count);
		~OpenGLIndexBuffer() override;

		void Bind() const override;
		void Unbind() const override;

		[[nodiscard]] FORCEINLINE int GetCount() const override { return m_Count; }
	private:
		int m_Count;
		uint32_t m_RendererID = 0;
	};
}
