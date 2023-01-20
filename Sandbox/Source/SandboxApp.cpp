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
			if (Dough::Input::IsKeyPressed(DH_KEY_LEFT_SHIFT))
				Dough::Application::Get().RequestRestart();
			else
				Dough::Application::Get().RequestFullClose();
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
