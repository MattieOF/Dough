#include "dhpch.h"
#include "Dough/Platform/Windows/WindowsInput.h"

#include <GLFW/glfw3.h>

#include "Dough/Core/Application.h"

namespace Dough
{
	bool WindowsInput::IsKeyPressedImpl(int keyCode)
	{
		const auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		return glfwGetKey(window, keyCode) == GLFW_PRESS;
	}

	bool WindowsInput::IsMouseButtonPressedImpl(int button)
	{
		const auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		return glfwGetMouseButton(window, button) == GLFW_PRESS;
	}

	std::pair<double, double>& WindowsInput::GetMousePosImpl()
	{
		const auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		std::pair<double, double> pos;
		glfwGetCursorPos(window, &pos.first, &pos.second);
		return pos;
	}
}
