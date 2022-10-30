#pragma once

#include "Window.h"
#include "Dough/Core/Core.h"
#include "Dough/ImGui/ImGuiLayer.h"
#include "Layers/LayerStack.h"

namespace Dough
{
	class Application
	{
	public:
		Application();
		virtual ~Application();

		[[nodiscard]] static inline Application& Get() { return *s_Instance; }

		bool Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* overlay);

		[[nodiscard]] inline Window& GetWindow() const { return *m_Window; }
	protected:
		bool m_RequestingRestart = false;
	private:
		bool OnWindowClosed(WindowCloseEvent e);
		bool OnWindowResized(WindowResizeEvent e);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;

		bool m_EnableImGui = true;
		ImGuiLayer* m_ImGuiLayer;

		LayerStack m_LayerStack;
		
		static Application* s_Instance;

		uint32_t m_VertexArray, m_VertexBuffer, m_IndexBuffer;
	};

	// To be defined by the client
	Application* CreateApplication();

}
