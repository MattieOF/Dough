#pragma once

#include <glad/gl.h>

#include "Dough/Renderer/Buffer.h"
#include "Dough/Renderer/Shader.h"

namespace Dough
{
	GLenum ShaderDataTypeToGLBaseType(ShaderDataType type);

	class OpenGLShader final : public Shader
	{
	public:
		OpenGLShader(const std::string& vertSource, const std::string& fragSource);
		~OpenGLShader() override;

		[[nodiscard]] uint32_t GetUniformLocation(const char* name) const override;

		void Bind() const override;
		void Unbind() const override;
	private:
		uint32_t m_RendererID;
	};
}
