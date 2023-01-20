#pragma once

#include "Dough/Core/Window.h"

#include <GLFW/glfw3.h>

#include "Dough/Renderer/GraphicsContext.h"

namespace Dough
{
	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowSpecification& spec);
		virtual ~WindowsWindow();

		void OnUpdate() override;

		[[nodiscard]] FORCEINLINE uint32_t GetWidth() const override { return m_Data.Width; }
		[[nodiscard]] FORCEINLINE uint32_t GetHeight() const override { return m_Data.Height; }

		FORCEINLINE void SetEventCallback(const EventCallbackFn& callback) override
		{
			m_Data.EventCallback = callback;
		}

		void SetVSync(bool enabled) override;
		[[nodiscard]] FORCEINLINE bool IsVSync() const override { return m_Data.VSync; }

		[[nodiscard]] FORCEINLINE const char* GetClipboardText() const override;
		void SetClipboardText(const char* text) override;

		void SetWindowTitle(const std::string& newTitle) override;

		[[nodiscard]] FORCEINLINE virtual void* GetNativeWindow() const override { return m_Window; }
	private:
		virtual void Init(const WindowSpecification& spec);
		virtual void Shutdown();
	private:
		GLFWwindow* m_Window;
		GraphicsContext* m_GraphicsContext;

		WindowData m_Data;
	};
}
