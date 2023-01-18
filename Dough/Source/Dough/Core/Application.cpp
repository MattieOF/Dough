#include "dhpch.h"
#include "Dough/Core/Application.h"
#include "glad/gl.h"

#include <fstream>

#include "Dough/Platform/OpenGL/OpenGLShader.h"
#include "Dough/Renderer/Renderer.h"
#include "Dough/Renderer/Shader.h"

namespace Dough
{
	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		DH_ASSERT_ERROR(s_Instance == nullptr, "Attempted to create a new Application instance, but one already exists.");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		DH_ENGINE_INFO("Render API: {0}.", Renderer::APIToString(Renderer::GetAPI()));
		m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));

		if (m_EnableImGui)
		{
			m_ImGuiLayer = new ImGuiLayer();
			PushOverlay(m_ImGuiLayer);
		}

		// Vertex buffer
		glGenVertexArrays(1, &m_VertexArray);
		glBindVertexArray(m_VertexArray);

		float verticies[3 * 6] = 
		{
			-0.5f, -0.5f, 0.0f, 1, 0, 0,
			 0.5f, -0.5f, 0.0f, 0, 1, 0,
			 0.0f,  0.5f, 0.0f, 0, 0, 1
		};

		m_VertexBuffer.reset(VertexBuffer::Create(verticies, DH_ARRAY_SIZE(verticies)));

		BufferLayout bufferLayout({
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float3, "a_Color" }
		});

		glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);
		int elementIndex = 0;
		for (auto element : bufferLayout)
		{
			glEnableVertexAttribArray(elementIndex);
			glVertexAttribPointer(elementIndex, GetShaderDataTypeElementCount(element.Type),
			                      ShaderDataTypeToGLBaseType(element.Type), element.Normalised ? GL_TRUE : GL_FALSE,
			                      bufferLayout.GetStride(),
			                      reinterpret_cast<const void*>(element.Offset));
			elementIndex++;
		}

		// Index buffer
		uint32_t indicies[3] = { 0, 1, 2 };
		m_IndexBuffer.reset(IndexBuffer::Create(indicies, DH_ARRAY_SIZE(indicies)));
		m_IndexBuffer->Bind();
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicies), indicies, GL_STATIC_DRAW);
		
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
			
			glBindVertexArray(m_VertexArray);
			glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);

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
