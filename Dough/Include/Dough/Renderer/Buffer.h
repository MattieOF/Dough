#pragma once

namespace Dough
{
	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() { }

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		static VertexBuffer* Create(float* verticies, uint32_t size);
	};

	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer() { }

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		static IndexBuffer* Create(uint32_t* indicies, uint32_t size);
	};
}
