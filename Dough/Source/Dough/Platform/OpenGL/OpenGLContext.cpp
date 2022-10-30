#include "dhpch.h"
#include "Dough/Platform/OpenGL/OpenGLContext.h"

#include "glad/gl.h"
#include "GLFW/glfw3.h"

namespace Dough
{
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		DH_ASSERT_FATAL(windowHandle, "OpenGL context window handle is null.");
	}

	void OpenGLContext::Init()
	{
		// Create GLFW context
		glfwMakeContextCurrent(m_WindowHandle);

		// Load GLAD
		int version = gladLoadGL(glfwGetProcAddress);
		DH_ASSERT_FATAL(version, "Failed to initialise OpenGL via GLAD!");
		DH_ENGINE_INFO("Loaded OpenGL v{0}", glGetString(GL_VERSION));
		DH_ENGINE_INFO("Rendering using {0}, drivers from {1}.", glGetString(GL_RENDERER), glGetString(GL_VENDOR));
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}
}
