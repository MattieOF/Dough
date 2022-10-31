#pragma once

#include "dhpch.h"

namespace Dough
{
	class Shader
	{
	public:
		Shader(const std::string& vertexSrc, const std::string fragSrc);
		~Shader();

		uint32_t GetUniformLocation(const char* name) const;

		void Bind() const;
		void Unbind() const;
	private:
		uint32_t m_RendererID;
	};
}
