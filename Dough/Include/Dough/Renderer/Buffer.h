#pragma once

namespace Dough
{
	// If this enum is extended, remember to update the relevant functions:
	// GetShaderDataTypeSize and GetShaderDataTypeElementCount in Buffer.cpp
	// ShaderDataTypeToGLBaseType in OpenGLShader.cpp
	enum class ShaderDataType : uint8_t
	{
		None,
		Float,
		Float2,
		Float3,
		Float4,
		Mat3,
		Mat4,
		Int,
		Int2,
		Int3,
		Int4,
		Bool
	};
	
	uint16_t GetShaderDataTypeSize(ShaderDataType type);
	uint16_t GetShaderDataTypeElementCount(ShaderDataType type);
	
	struct BufferElement
	{
		std::string Name;
		ShaderDataType Type;
		uint16_t Size;
		uint16_t Offset;
		bool Normalised;

		BufferElement() { }

		BufferElement(ShaderDataType type, const std::string& name, bool normalised = false)
			: Name(name), Type(type), Size(GetShaderDataTypeSize(type)), Offset(0), Normalised(normalised)
		{}
	};

	class BufferLayout
	{
	public:
		BufferLayout() = default;

		BufferLayout(const std::initializer_list<BufferElement>& elements)
			: m_Elements(elements)
		{
			CalculateOffsetsAndStride();
		}

		[[nodiscard]] inline const std::vector<BufferElement>& GetElements() const { return m_Elements; }
		[[nodiscard]] inline uint16_t GetStride() const { return m_Stride; }

		[[nodiscard]] std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
		[[nodiscard]] std::vector<BufferElement>::iterator end()   { return m_Elements.end(); }
		[[nodiscard]] std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }
		[[nodiscard]] std::vector<BufferElement>::const_iterator end()   const { return m_Elements.end(); }
	private:
		void CalculateOffsetsAndStride();

		uint16_t m_Stride = 0;
		std::vector<BufferElement> m_Elements;
	};

	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() { }

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		[[nodiscard]] virtual inline int GetCount() const = 0;

		inline virtual void SetLayout(BufferLayout& layout) { m_Layout = layout; }
		inline virtual BufferLayout& GetLayout() { return m_Layout; }

		static VertexBuffer* Create(float* verticies, int count);
	private:
		BufferLayout m_Layout;
	};

	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer() { }

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		[[nodiscard]] virtual inline int GetCount() const = 0;

		static IndexBuffer* Create(uint32_t* indicies, int count);
	};
}
