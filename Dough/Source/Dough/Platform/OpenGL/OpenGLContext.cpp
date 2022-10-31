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
		const int version = gladLoadGL(glfwGetProcAddress);
		DH_ASSERT_FATAL(version, "Failed to initialise OpenGL via GLAD!");
		DH_ENGINE_INFO("Loaded OpenGL v{0}", glGetString(GL_VERSION));
		DH_ENGINE_INFO("Rendering using {0}, drivers from {1}.", glGetString(GL_RENDERER), glGetString(GL_VENDOR));

		// Initialise OpenGL error callback, if not dist build
#ifndef DH_DIST
        glEnable(GL_DEBUG_OUTPUT);
		glDebugMessageCallback(OpenGLContext::GLErrorCallback, nullptr);
#endif
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}

    // Code from https://gist.github.com/liam-middlebrook/c52b069e4be2d87a6d2f
    // Edited to work with our logging and assert system
	void OpenGLContext::GLErrorCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
	{
#ifndef DH_SHOW_GL_NOTIFICATIONS
        if (severity == GL_DEBUG_SEVERITY_NOTIFICATION)
            return;
#endif

        char* sourceText;
        char* typeText;
        char* severityText;

        switch (source) {
        case GL_DEBUG_SOURCE_API:
            sourceText = "API";
            break;

        case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
            sourceText = "Window System";
            break;

        case GL_DEBUG_SOURCE_SHADER_COMPILER:
            sourceText = "Shader Compiler";
            break;

        case GL_DEBUG_SOURCE_THIRD_PARTY:
            sourceText = "Third Party";
            break;

        case GL_DEBUG_SOURCE_APPLICATION:
            sourceText = "Application";
            break;

        case GL_DEBUG_SOURCE_OTHER:
            sourceText = "Unknown";
            break;

        default:
            sourceText = "Unknown";
            break;
        }

        switch (type) {
        case GL_DEBUG_TYPE_ERROR:
            typeText = "Error";
            break;

        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
            typeText = "Deprecated Behaviour";
            break;

        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
            typeText = "Undefined Behaviour";
            break;

        case GL_DEBUG_TYPE_PORTABILITY:
            typeText = "Portability";
            break;

        case GL_DEBUG_TYPE_PERFORMANCE:
            typeText = "Performance";
            break;

        case GL_DEBUG_TYPE_OTHER:
            typeText = "Other";
            break;

        case GL_DEBUG_TYPE_MARKER:
            typeText = "Marker";
            break;

        default:
            typeText = "Unknown";
            break;
        }

        switch (severity) {
        case GL_DEBUG_SEVERITY_HIGH:
            severityText = "High";
            break;

        case GL_DEBUG_SEVERITY_MEDIUM:
            severityText = "Medium";
            break;

        case GL_DEBUG_SEVERITY_LOW:
            severityText = "Low";
            break;

        case GL_DEBUG_SEVERITY_NOTIFICATION:
            severityText = "Notification";
            break;

        default:
            severityText = "Unknown";
            break;
        }

        DH_ENGINE_ERROR("OpenGL Error ({0}, id: {4}): from {1}, {2}: {3}", severityText, sourceText, typeText, message, id);
        DH_ASSERT_ERROR(severity == GL_DEBUG_SEVERITY_NOTIFICATION);
	}
}
