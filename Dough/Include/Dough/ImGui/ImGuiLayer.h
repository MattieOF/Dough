#pragma once

#include "Dough/Core/Layers/Layer.h"
#include "Dough/Events/MouseEvent.h"

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

		bool OnMouseMoved(MouseMovedEvent e);
		bool OnMouseButtonDown(MouseButtonPressedEvent e);
		bool OnMouseButtonUp(MouseButtonReleasedEvent e);
	private:
		float m_Time = 0.0f;
	};
}
