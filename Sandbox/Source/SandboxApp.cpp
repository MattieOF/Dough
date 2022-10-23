#include <Dough.h>

#include "Dough/ImGui/ImGuiLayer.h"

class ExampleLayer : public Dough::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{}

	void OnUpdate() override
	{
		// DH_TRACE("Updating example layer");
	}

	void OnEvent(Dough::Event& event) override
	{
		// DH_TRACE("{0}", event);
	}
};

class Sandbox : public Dough::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
		PushOverlay(new Dough::ImGuiLayer());
	}

	~Sandbox()
	{

	}
};

Dough::Application* Dough::CreateApplication()
{
	return new Sandbox();
}
