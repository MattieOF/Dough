#include <Dough.h>
#include <imgui.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include "SandboxLog.h"

class ExampleLayer : public Dough::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{}

	void OnUpdate() override
	{
		if (Dough::Input::IsKeyPressed(DH_KEY_ESCAPE))
		{
			Dough::Application::Get().RequestClose();
		}
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
};

DH_DECLARE_LOGGER_CPP(Sandbox);

class Sandbox : public Dough::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
		m_RequestingRestart = true;

		DH_DEFINE_LOGGER(Sandbox);
		SANDBOX_INFO("Test");
	}

	~Sandbox()
	{

	}
};

Dough::Application* Dough::CreateApplication()
{
	return new Sandbox();
}
