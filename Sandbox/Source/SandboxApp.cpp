#include <Dough.h>
#include <imgui.h>

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
			// TODO: This is terrible, add functions to do this
			Dough::WindowCloseEvent e;
			Dough::Application::Get().OnEvent(e);
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
	Sandbox()
	{
		PushLayer(new ExampleLayer());
		m_RequestingRestart = true;
	}

	~Sandbox()
	{

	}
};

Dough::Application* Dough::CreateApplication()
{
	return new Sandbox();
}
