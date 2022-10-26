#include "dhpch.h"
#include "Dough/Core/Application.h"
#include "glad/gl.h"

namespace Dough
{
	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		DH_ASSERT_ERROR(s_Instance == nullptr, "Attempted to create a new Application instance, but one already exists.");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));
	}

	Application::~Application()
	{
		// Detach all layers from top to bottom
		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
			(*--it)->OnDetach();

		s_Instance = nullptr;
	}

	bool Application::Run()
	{
		while (m_Running)
		{
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			// Update all layers from the base layer up
			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

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
		// TODO: Abstract this per graphics platform
		glViewport(0, 0, e.GetWidth(), e.GetHeight());
		return false;
	}
}
