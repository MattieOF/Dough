#pragma once

#include "Dough/Renderer/Shader.h"

namespace Dough
{
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& vertSource, const std::string& fragSource);
		virtual ~OpenGLShader() override;

		[[nodiscard]] virtual uint32_t GetUniformLocation(const char* name) const override;

		virtual void Bind() const override;
		virtual void Unbind() const override;
	private:
		uint32_t m_RendererID;
	};
}
