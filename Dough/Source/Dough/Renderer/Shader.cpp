// TODO: Make this an abstract class to be implemented per graphics platform.

#include "dhpch.h"
#include "Dough/Renderer/Shader.h"

#include <glad/gl.h>

namespace Dough
{
	Shader::Shader(const std::string& vertexSrc, const std::string fragSrc)
	{
		// Compile vertex shader
		uint32_t vertex = glCreateShader(GL_VERTEX_SHADER);
		const char* vertexSrcCStr = vertexSrc.c_str();
		glShaderSource(vertex, 1, &vertexSrcCStr, nullptr);
		glCompileShader(vertex);

		// Error check vertex compilation
		int32_t isCompiled = 0;
		glGetShaderiv(vertex, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			int32_t logLength = 0;
			glGetShaderiv(vertex, GL_INFO_LOG_LENGTH, &logLength);

			char* error = static_cast<char*>(_malloca(logLength * sizeof(char)));
			glGetShaderInfoLog(vertex, logLength, &logLength, &error[0]);

			DH_ENGINE_ERROR("Failed to compile vertex shader. Error: {0}", &error[0]);
			DH_ASSERT_ERROR(false);

			glDeleteShader(vertex);
			return;
		}

		// Compile frag shader
		uint32_t frag = glCreateShader(GL_FRAGMENT_SHADER);
		const char* fragSrcCStr = fragSrc.c_str();
		glShaderSource(frag, 1, &fragSrcCStr, nullptr);
		glCompileShader(frag);

		// Error check frag compilation
		isCompiled = 0;
		glGetShaderiv(frag, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			int32_t logLength = 0;
			glGetShaderiv(frag, GL_INFO_LOG_LENGTH, &logLength);

			char* error = static_cast<char*>(_malloca(logLength * sizeof(char)));
			glGetShaderInfoLog(frag, logLength, &logLength, &error[0]);

			DH_ENGINE_ERROR("Failed to compile fragment shader. Error: {0}", &error[0]);
			DH_ASSERT_ERROR(false);

			glDeleteShader(frag);
			return;
		}

		// Create program and attach shaders
		m_RendererID = glCreateProgram();
		glAttachShader(m_RendererID, vertex);
		glAttachShader(m_RendererID, frag);
		glLinkProgram(m_RendererID);

		// Error check program linking
		int32_t isLinked = 0;
		glGetProgramiv(m_RendererID, GL_LINK_STATUS, &isLinked);
		if (isLinked == GL_FALSE)
		{
			int32_t logLength = 0;
			glGetProgramiv(m_RendererID, GL_INFO_LOG_LENGTH, &logLength);

			char* error = static_cast<char*>(_malloca(logLength * sizeof(char)));
			glGetProgramInfoLog(m_RendererID, logLength, &logLength, &error[0]);

			DH_ENGINE_ERROR("Failed to link shader program. Error: {0}", &error[0]);
			DH_ASSERT_ERROR(false);

			glDeleteProgram(m_RendererID);
			glDeleteShader(vertex);
			glDeleteShader(frag);

			return;
		}

		glDetachShader(m_RendererID, vertex);
		glDetachShader(m_RendererID, frag);
		glDeleteShader(vertex);
		glDeleteShader(frag);
	}

	Shader::~Shader()
	{
		glDeleteProgram(m_RendererID);
	}

	uint32_t Shader::GetUniformLocation(const char* name) const
	{
		return glGetUniformLocation(m_RendererID, name);
	}

	void Shader::Bind() const
	{
		glUseProgram(m_RendererID);
	}

	void Shader::Unbind() const
	{
		glUseProgram(0);
	}
}
