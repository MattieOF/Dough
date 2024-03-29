#include "dhpch.h"
#include "Dough/Platform/OpenGL/OpenGLShader.h"

#include <glad/gl.h>

namespace Dough
{
	GLenum ShaderDataTypeToGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
			case ShaderDataType::None:   return 0;

			case ShaderDataType::Float:  
			case ShaderDataType::Float2: 
			case ShaderDataType::Float3: 
			case ShaderDataType::Float4: 
			case ShaderDataType::Mat3:   
			case ShaderDataType::Mat4:   return GL_FLOAT;

			case ShaderDataType::Int:    
			case ShaderDataType::Int2:   
			case ShaderDataType::Int3:   
			case ShaderDataType::Int4:   return GL_INT;

			case ShaderDataType::Bool:   return GL_BOOL;
		}

		DH_ASSERT_ERROR(false, "Unknown shader data type! (id: %i)", (int)type);
		return 0;
	}

	OpenGLShader::OpenGLShader(const std::string& vertSource, const std::string& fragSource)
	{
		// Compile vertex shader
		const uint32_t vertex = glCreateShader(GL_VERTEX_SHADER);
		const char* vertexSrcCStr = vertSource.c_str();
		glShaderSource(vertex, 1, &vertexSrcCStr, nullptr);
		glCompileShader(vertex);

		// Error check vertex compilation
		int32_t isCompiled = 0;
		glGetShaderiv(vertex, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			int32_t logLength = 0;
			glGetShaderiv(vertex, GL_INFO_LOG_LENGTH, &logLength);

			auto error = static_cast<char*>(_malloca(logLength * sizeof(char)));
			glGetShaderInfoLog(vertex, logLength, &logLength, &error[0]);

			DH_ENGINE_ERROR("Failed to compile vertex shader. Error: {0}", &error[0]);
			DH_ASSERT_ERROR(false);

			glDeleteShader(vertex);
			return;
		}

		// Compile frag shader
		const uint32_t frag = glCreateShader(GL_FRAGMENT_SHADER);
		const char* fragSrcCStr = fragSource.c_str();
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

			auto error = static_cast<char*>(_malloca(logLength * sizeof(char)));
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

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_RendererID);
	}

	uint32_t OpenGLShader::GetUniformLocation(const char* name) const
	{
		return glGetUniformLocation(m_RendererID, name);
	}

	void OpenGLShader::Bind() const
	{
		glUseProgram(m_RendererID);
	}

	void OpenGLShader::Unbind() const
	{
		glUseProgram(0);
	}
}
