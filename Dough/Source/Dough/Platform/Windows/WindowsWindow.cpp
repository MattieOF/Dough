#include "dhpch.h"
#include "Dough/Platform/Windows/WindowsWindow.h"

#include "Dough/Core/Log.h"

#include <glad/gl.h>

namespace Dough
{
	static bool s_GLFWInitialised = false;

	static void GLFWErrorCallback(int error, const char* desc)
	{
		DH_ENGINE_ERROR("GLFW Error ({0}): {1}", error, desc);
	}

	Window* Window::Create(const WindowSpecification& spec)
	{
		return new WindowsWindow(spec);
	}

	WindowsWindow::WindowsWindow(const WindowSpecification& spec)
	{
		WindowsWindow::Init(spec);
	}

	WindowsWindow::~WindowsWindow()
	{
		WindowsWindow::Shutdown();
	}

	void WindowsWindow::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}

	void WindowsWindow::SetVSync(bool enabled)
	{
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		m_Data.VSync = enabled;
	}

	const char* WindowsWindow::GetClipboardText() const
	{
		return glfwGetClipboardString(m_Window);
	}

	void WindowsWindow::SetClipboardText(const char* text)
	{
		glfwSetClipboardString(m_Window, text);
	}

	void WindowsWindow::Init(const WindowSpecification& spec)
	{
		m_Data.Title = spec.Title;
		m_Data.Width = spec.Width;
		m_Data.Height = spec.Height;

		DH_ENGINE_INFO("Creating window; Title: {0}, Size: ({1}, {2})", spec.Title, spec.Width, spec.Height);

		if (!s_GLFWInitialised)
		{
			DH_ENGINE_INFO("Initialising GLFW...");
			const int success = glfwInit();
			DH_ASSERT_FATAL(success, "Failed to initialise GLFW.");
			s_GLFWInitialised = true;
		}

		m_Window = glfwCreateWindow(spec.Width, spec.Height, spec.Title.c_str(), nullptr, nullptr);
		DH_ASSERT_FATAL(m_Window, "Failed to create GLFW window!");
		glfwMakeContextCurrent(m_Window);
		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);

		// Load GLAD
		int version = gladLoadGL(glfwGetProcAddress);
		DH_ASSERT_FATAL(version, "Failed to initialise OpenGL via GLAD!");
		DH_ENGINE_INFO("Loaded OpenGL v{0}.{1}", GLAD_VERSION_MAJOR(version), GLAD_VERSION_MINOR(version));

		// Setup GLFW event callbacks
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
		{
			// Get data struct from the window
			WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

			// Update data structs width and height values
			data.Width = width;
			data.Height = height;

			// Create a resize event and dispatch it
			WindowResizeEvent e(width, height);
			data.EventCallback(e);
		});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
		{
			WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
			WindowCloseEvent e;
			data.EventCallback(e);
		});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

			switch(action)
			{
				case GLFW_PRESS:
				{
					KeyPressedEvent e(key, false);
					data.EventCallback(e);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent e(key);
					data.EventCallback(e);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressedEvent e(key, true);
					data.EventCallback(e);
					break;
				}
				default: break;
			}
		});

		glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned codepoint)
		{
			WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
			KeyTypedEvent e(codepoint);
			data.EventCallback(e);
		});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
		{
			WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

			switch (action)
			{
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent e(button);
					data.EventCallback(e);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent e(button);
					data.EventCallback(e);
					break;
				}
				default: break;
			}
		});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xoffset, double yoffset)
		{
			WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
			MouseScrolledEvent e(xoffset, yoffset);
			data.EventCallback(e);
		});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xpos, double ypos)
		{
			WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
			MouseMovedEvent e(xpos, ypos);
			data.EventCallback(e);
		});

		glfwSetErrorCallback(GLFWErrorCallback);
	}

	void WindowsWindow::Shutdown()
	{
		glfwDestroyWindow(m_Window);
	}
}
