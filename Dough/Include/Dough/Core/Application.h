#pragma once

#include "Window.h"
#include "Dough/Core/Core.h"
#include "Layers/LayerStack.h"

namespace Dough
{
	class DOUGH_API Application
	{
	public:
		Application();
		virtual ~Application();

		[[nodiscard]] static inline Application& Get() { return *s_Instance; }

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* overlay);

		[[nodiscard]] inline Window& GetWindow() const { return *m_Window; }
	private:
		bool OnWindowClosed(WindowCloseEvent e);
		bool OnWindowResized(WindowResizeEvent e);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;

		static Application* s_Instance;
	};

	// To be defined by the client
	Application* CreateApplication();

}
