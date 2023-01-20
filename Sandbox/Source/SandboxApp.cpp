#include <Dough.h>
#include <fstream>
#include <imgui.h>
#include <Dough/Renderer/Renderer.h>
#include <Dough/Renderer/Shader.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include "SandboxLog.h"

class ExampleLayer : public Dough::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
		// Initialise test vertex
		float verticies[3 * 6] =
		{
			-0.8f, -0.5f, 0.0f, 1, 0, 0,
			 -0.2f, -0.5f, 0.0f, 0, 1, 0,
			 -0.5f,  0.5f, 0.0f, 0, 0, 1
		};
		std::shared_ptr<Dough::VertexBuffer> vertexBuffer(Dough::VertexBuffer::Create(verticies, DH_ARRAY_SIZE(verticies)));
		Dough::BufferLayout bufferLayout({
			{Dough::ShaderDataType::Float3, "a_Position" },
			{Dough::ShaderDataType::Float3, "a_Color" }
		});
		vertexBuffer->SetLayout(bufferLayout);

		// Initialise test indicies
		uint32_t indicies[3] = { 0, 1, 2 };
		std::shared_ptr<Dough::IndexBuffer> indexBuffer(Dough::IndexBuffer::Create(indicies, DH_ARRAY_SIZE(indicies)));

		// Initialise vertex array
		m_VertexArray.reset(Dough::VertexArray::Create());
		m_VertexArray->AddVertexBuffer(vertexBuffer);
		m_VertexArray->SetIndexBuffer(indexBuffer);

		// Initialise test square
		float squareVerticies[4 * 6] =
		{
			0.2f, 0.5f, 0.0f, 1, 0, 0,
			0.8f, 0.5f, 0.0f, 0, 1, 0,
			0.8f, -0.5f, 0.0f, 0, 0, 1,
			0.2f, -0.5f, 0.0f, 0.5f, 0.5f, 0.5f
		};
		std::shared_ptr<Dough::VertexBuffer> squareVertexBuffer(Dough::VertexBuffer::Create(squareVerticies, DH_ARRAY_SIZE(squareVerticies)));
		squareVertexBuffer->SetLayout(bufferLayout);

		uint32_t squareIndicies[6] = { 0, 1, 2, 2, 0, 3 };
		std::shared_ptr<Dough::IndexBuffer> squareIndexBuffer(Dough::IndexBuffer::Create(squareIndicies, DH_ARRAY_SIZE(squareIndicies)));

		m_SquareVertexArray.reset(Dough::VertexArray::Create());
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

		m_Shader.reset(Dough::Shader::Create(vertSrcStream.str(), fragSrcStream.str()));
	}

	void OnUpdate() override
	{
		if (Dough::Input::IsKeyPressed(DH_KEY_ESCAPE))
		{
			if (Dough::Input::IsKeyPressed(DH_KEY_LEFT_SHIFT))
				Dough::Application::Get().RequestRestart();
			else
				Dough::Application::Get().RequestFullClose();
		}
		
		m_Shader->Bind();
		Dough::Renderer::Submit(m_VertexArray);
		Dough::Renderer::Submit(m_SquareVertexArray);
	}

	void OnEvent(Dough::Event& event) override
	{
		// DH_TRACE("{0}", event);
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Test");
		ImGui::Text("Hello World");
		ImGui::End();
	}

private:
	std::shared_ptr<Dough::VertexArray> m_VertexArray, m_SquareVertexArray;
	std::shared_ptr<Dough::Shader> m_Shader;
};

class Sandbox : public Dough::Application
{
public:
	Sandbox(Dough::ApplicationSpecification spec)
		: Application(spec)
	{
		DH_DEFINE_LOGGER(Sandbox);
		SANDBOX_INFO("Test");

		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{

	}
};

Dough::Application* Dough::CreateApplication()
{
	ApplicationSpecification spec;
	spec.Name = "Sandbox App";
	return new Sandbox(spec);
}
