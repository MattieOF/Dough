#pragma once

#include "Dough/Core/Window.h"

#include <GLFW/glfw3.h>

namespace Dough
{
	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowSpecification& spec);
		virtual ~WindowsWindow();

		void OnUpdate() override;

		[[nodiscard]] inline uint32_t GetWidth() const override { return m_Data.Width; }
		[[nodiscard]] inline uint32_t GetHeight() const override { return m_Data.Height; }

		inline void SetEventCallback(const EventCallbackFn& callback) override
		{
			m_Data.EventCallback = callback;
		}

		void SetVSync(bool enabled) override;
		[[nodiscard]] bool IsVSync() const override { return m_Data.VSync; }
	private:
		virtual void Init(const WindowSpecification& spec);
		virtual void Shutdown();
	private:
		GLFWwindow* m_Window;
		WindowData m_Data;
	};
}
