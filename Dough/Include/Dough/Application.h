#pragma once

#include "Dough/Core.h"
#include "Dough/Events/Event.h"

namespace Dough
{
	class DOUGH_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	// To be defined by the client
	Application* CreateApplication();

}
