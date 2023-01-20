#pragma once

#include "Dough/Renderer/VertexArray.h"

namespace Dough
{
	class OpenGLVertexArray final : public VertexArray
	{
	public:
		OpenGLVertexArray();
		~OpenGLVertexArray() override;

		void Bind() const override;
		void Unbind() const override;

		void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& buffer) override;
		void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& buffer) override;

		[[nodiscard]] FORCEINLINE const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() override { return m_VertexBuffers; }
		[[nodiscard]] FORCEINLINE const std::shared_ptr<IndexBuffer>& GetIndexBuffer() override { return m_IndexBuffer; }

	private:
		std::vector<std::shared_ptr<VertexBuffer>> m_VertexBuffers;
		std::shared_ptr<IndexBuffer> m_IndexBuffer;
		uint32_t m_RendererID;
	};
}
