#include "dhpch.h"

#include "Dough/Core/Application.h"

#include <fstream>
#include <glad/gl.h>

#include "Dough/Platform/OpenGL/OpenGLShader.h"
#include "Dough/Renderer/Renderer.h"
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
		DH_ENGINE_INFO("Render API: {0}.", Renderer::APIToString(Renderer::GetAPI()));
		m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));
		m_Window->SetWindowTitle(spec.Name);

		// Initialise ImGui if enabled
		if (m_EnableImGui)
		{
			m_ImGuiLayer = new ImGuiLayer();
			PushOverlay(m_ImGuiLayer);
		}

		// Initialise test vertex
		float verticies[3 * 6] = 
		{
			-0.8f, -0.5f, 0.0f, 1, 0, 0,
			 -0.2f, -0.5f, 0.0f, 0, 1, 0,
			 -0.5f,  0.5f, 0.0f, 0, 0, 1
		};
		m_VertexBuffer.reset(VertexBuffer::Create(verticies, DH_ARRAY_SIZE(verticies)));
		BufferLayout bufferLayout({
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float3, "a_Color" }
		});
		m_VertexBuffer->SetLayout(bufferLayout);
		
		// Initialise test indicies
		uint32_t indicies[3] = { 0, 1, 2 };
		m_IndexBuffer.reset(IndexBuffer::Create(indicies, DH_ARRAY_SIZE(indicies)));

		// Initialise vertex array
		m_VertexArray.reset(VertexArray::Create());
		m_VertexArray->AddVertexBuffer(m_VertexBuffer);
		m_VertexArray->SetIndexBuffer(m_IndexBuffer);

		// Initialise test square
		float squareVerticies[4 * 6] =
		{
			0.2f, 0.5f, 0.0f, 1, 0, 0,
			0.8f, 0.5f, 0.0f, 0, 1, 0,
			0.8f, -0.5f, 0.0f, 0, 0, 1,
			0.2f, -0.5f, 0.0f, 0.5f, 0.5f, 0.5f
		};
		std::shared_ptr<VertexBuffer> squareVertexBuffer(VertexBuffer::Create(squareVerticies, DH_ARRAY_SIZE(squareVerticies)));
		squareVertexBuffer->SetLayout(bufferLayout);

		uint32_t squareIndicies[6] = { 0, 1, 2, 2, 0, 3 };
		std::shared_ptr<IndexBuffer> squareIndexBuffer(IndexBuffer::Create(squareIndicies, DH_ARRAY_SIZE(squareIndicies)));

		m_SquareVertexArray.reset(VertexArray::Create());
		m_SquareVertexArray->AddVertexBuffer(squareVertexBuffer);
		m_SquareVertexArray->SetIndexBuffer(squareIndexBuffer);

		// Initialise test shader
		std::ifstream fragSrc;
		std::stringstream fragSrcStream;
		fragSrc.open("Content/Shaders/Test.frag");
		fragSrcStream << fragSrc.rdbuf();
		std::ifstream vertSrc;
		std::stringstream vertSrcStream;
		vertSrc.open("Content/Shaders/Test.vert");
		vertSrcStream << vertSrc.rdbuf();

		m_Shader.reset(Shader::Create(vertSrcStream.str(), fragSrcStream.str()));
	}

	Application::~Application()
	{
		s_Instance = nullptr;
	}

	bool Application::Run()
	{
		while (m_Running)
		{
			glClearColor(0.15f, 0.15f, 0.15f, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			m_Shader->Bind();

			m_VertexArray->Bind();
			glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);

			m_SquareVertexArray->Bind();
			glDrawElements(GL_TRIANGLES, m_SquareVertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);

			// Update all layers from the base layer up
			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

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
		// TODO: Abstract this per graphics platform
		glViewport(0, 0, e.GetWidth(), e.GetHeight());
		return false;
	}
}
