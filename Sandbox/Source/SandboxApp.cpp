#include <Dough.h>

class Sandbox : public Dough::Application
{
public:
	Sandbox()
	{

	}

	~Sandbox()
	{

	}
};

Dough::Application* Dough::CreateApplication()
{
	return new Sandbox();
}
