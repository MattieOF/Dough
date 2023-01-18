#pragma once

#include "Dough/Renderer/Buffer.h"

namespace Dough
{
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(float* verticies, int count);
		virtual ~OpenGLVertexBuffer() override;

		virtual void Bind() const override;
		virtual void Unbind() const override;

		[[nodiscard]] inline virtual int GetCount() const override { return m_Count; }
	private:
		int m_Count;
		uint32_t m_RendererID = 0;
	};

	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(uint32_t* indicies, int count);
		virtual ~OpenGLIndexBuffer() override;

		virtual void Bind() const override;
		virtual void Unbind() const override;

		[[nodiscard]] inline virtual int GetCount() const override { return m_Count; }
	private:
		int m_Count;
		uint32_t m_RendererID = 0;
	};
}
