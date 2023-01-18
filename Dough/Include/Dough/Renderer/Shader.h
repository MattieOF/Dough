#pragma once

#include "dhpch.h"

namespace Dough
{
	class Shader
	{
	public:
		virtual ~Shader() { };

		[[nodiscard]] virtual uint32_t GetUniformLocation(const char* name) const = 0;
		
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		static Shader* Create(const std::string& vertSource, const std::string& fragSource);
	};
}
