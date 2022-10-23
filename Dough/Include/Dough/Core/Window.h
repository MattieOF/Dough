#pragma once

#include "dhpch.h"

#include "Dough/Core/Core.h"
#include "Dough/Events/Events.h"

namespace Dough
{
	struct WindowSpecification
	{
		std::string Title;
		uint32_t Width, Height;

		WindowSpecification(const std::string& title = "Dough App",
							uint32_t width = 1280, uint32_t height = 720)
								: Title(title), Width(width), Height(height)
		{
		}
	};
	
	class DOUGH_API Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() { }

		virtual void OnUpdate() = 0;

		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;

		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;

		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		static Window* Create(const WindowSpecification& spec = WindowSpecification());
		
		struct WindowData
		{
			std::string Title;
			uint32_t Width, Height;
			bool VSync;

			EventCallbackFn EventCallback;
		};
	};
}
