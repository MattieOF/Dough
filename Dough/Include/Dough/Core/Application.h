#pragma once

#include "Window.h"
#include "Dough/Core/Core.h"
#include "Dough/ImGui/ImGuiLayer.h"
#include "Layers/LayerStack.h"

namespace Dough
{
	class Shader;

	struct ApplicationSpecification
	{
		std::string Name = "Dough Application";
		bool EnableImGui = true;
	};

	class Application
	{
	public:
		Application(ApplicationSpecification spec);
		virtual ~Application();

		[[nodiscard]] static inline Application& Get() { return *s_Instance; }

		bool Run();

		void OnEvent(Event& e);

		void RequestClose();
		void RequestFullClose();
		void RequestRestart();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* overlay);

		[[nodiscard]] FORCEINLINE Window& GetWindow() const { return *m_Window; }
	protected:
		bool m_RequestingRestart = false;
	private:
		bool OnWindowClosed(WindowCloseEvent e);
		bool OnWindowResized(WindowResizeEvent e);

		ApplicationSpecification m_Specification;

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;

		bool m_EnableImGui = true;
		ImGuiLayer* m_ImGuiLayer;

		LayerStack m_LayerStack;
		
		static Application* s_Instance;
	};

	// To be defined by the client
	Application* CreateApplication();

}
