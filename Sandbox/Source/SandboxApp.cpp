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
		if (Dough::Input::IsMouseButtonPressed(DH_MOUSE_BUTTON_LEFT))
			DH_TRACE("LMB down poggers");

		if (Dough::Input::IsKeyPressed(DH_KEY_W))
			DH_TRACE("Move forward");

		if (Dough::Input::IsKeyPressed(DH_KEY_ESCAPE))
		{
			// TODO: This is terrible, add functions to do this
			Dough::WindowCloseEvent e;
			Dough::Application::Get().OnEvent(e);
		}
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
