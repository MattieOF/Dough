#pragma once

#include "glad/gl.h"
#include "Dough/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Dough
{
	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* windowHandle);

		void Init() override;
		void SwapBuffers() override;

		static void GLErrorCallback(GLenum source,
			GLenum type,
			GLuint id,
			GLenum severity,
			GLsizei length,
			const GLchar* message,
			const void* userParam);
	private:
		GLFWwindow* m_WindowHandle;
	};
}
