#pragma once

#include "Dough/Core/Layers/Layer.h"
#include "Dough/Events/Events.h"

struct ImGuiIO;

namespace Dough
{
	class DOUGH_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach() override;
		void OnDetach() override;
		void OnUpdate() override;
		void OnEvent(Event& event) override;

	private:
		bool OnMouseMoved(MouseMovedEvent& e) const;
		bool OnMouseButtonDown(MouseButtonPressedEvent& e) const;
		bool OnMouseButtonUp(MouseButtonReleasedEvent& e) const;
		bool OnMouseScrolled(MouseScrolledEvent& e) const;
		bool OnKeyPressed(KeyPressedEvent& e) const;
		bool OnKeyReleased(KeyReleasedEvent& e) const;
		bool OnKeyTyped(KeyTypedEvent& e) const;
		bool OnWindowResize(WindowResizeEvent& e) const;
		
		static const char* GetClipboardTextCallback(void* userData);
		static void SetClipboardTextCallback(void* userData, const char* text);

	private:
		ImGuiIO* m_IO = nullptr;
		float m_Time = 0.0f;
	};
}
