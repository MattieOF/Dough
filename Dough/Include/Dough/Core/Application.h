#pragma once

#include "Window.h"
#include "Dough/Core/Core.h"

namespace Dough
{
	class DOUGH_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	private:
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
	};

	// To be defined by the client
	Application* CreateApplication();

}
