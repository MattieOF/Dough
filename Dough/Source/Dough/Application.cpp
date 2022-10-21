#include "Dough/Application.h"

#include "Dough/Log.h"
#include "Dough/Events/ApplicationEvent.h"

namespace Dough
{
	Application::Application()
	{

	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		WindowResizeEvent e(1280, 720);
		if (e.IsInCategory(EC_Application))
		{
			DH_TRACE(e);
		}
		if (e.IsInCategory(EC_Input))
		{
			DH_TRACE(e);
		}

		while (true);
	}
}
