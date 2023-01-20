#include "dhpch.h"

#include "Dough/Core/Application.h"

#include <fstream>

#include "Dough/Renderer/Renderer.h"
#include "Dough/Renderer/RenderCommand.h"
#include "Dough/Renderer/Shader.h"

namespace Dough
{
	Application* Application::s_Instance = nullptr;

	Application::Application(ApplicationSpecification spec)
	{
		// Initialise instance
		DH_ASSERT_ERROR(s_Instance == nullptr, "Attempted to create a new Application instance, but one already exists.");
		s_Instance = this;

		m_Specification = spec;

		// Create window
		m_Window = std::unique_ptr<Window>(Window::Create());
		DH_ENGINE_INFO("Render API: {0}.", RendererAPI::GetAPIString(Renderer::GetAPI()));
		m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));
		m_Window->SetWindowTitle(spec.Name);

		// Initialise ImGui if enabled
		if (m_EnableImGui)
		{
			m_ImGuiLayer = new ImGuiLayer();
			PushOverlay(m_ImGuiLayer);
		}
	}

	Application::~Application()
	{
		s_Instance = nullptr;
	}

	bool Application::Run()
	{
		while (m_Running)
		{
			RenderCommand::SetClearColor(glm::vec4(0.15f, 0.15f, 0.15f, 1));
			RenderCommand::Clear();

			Renderer::BeginScene();

			// Update all layers from the base layer up
			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();
			
			Renderer::EndScene();

			if (m_EnableImGui)
			{
				DH_ASSERT_ERROR(m_ImGuiLayer, "Attempting to render ImGui, but ImGui layer is null.");
				m_ImGuiLayer->Begin();
				for (Layer* layer : m_LayerStack)
					layer->OnImGuiRender();
				m_ImGuiLayer->End();
			}

			m_Window->OnUpdate();
		}

		return m_RequestingRestart;
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClosed));
		dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(Application::OnWindowResized));

		// Propagate the event to all layers, starting with the topmost layer/overlay, down to the base layer. 
		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			(*--it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}

	void Application::RequestClose()
	{
		m_Running = false;
	}

	void Application::RequestFullClose()
	{
		m_RequestingRestart = false;
		m_Running = false;
	}

	void Application::RequestRestart()
	{
		m_RequestingRestart = true;
		m_Running = false;
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* overlay)
	{
		m_LayerStack.PushOverlay(overlay);
	}

	void Application::PopLayer(Layer* layer)
	{
		m_LayerStack.PopLayer(layer);
	}

	void Application::PopOverlay(Layer* overlay)
	{
		m_LayerStack.PopOverlay(overlay);
	}

	bool Application::OnWindowClosed(WindowCloseEvent e)
	{
		m_Running = false;
		return true;
	}

	bool Application::OnWindowResized(WindowResizeEvent e)
	{
		RenderCommand::SetViewport(glm::vec2(e.GetWidth(), e.GetHeight()));
		return false;
	}
}
