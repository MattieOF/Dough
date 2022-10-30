#pragma once

#include "Dough/Core/Layers/Layer.h"
#include "Dough/Events/Events.h"

struct ImGuiIO;

namespace Dough
{
	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();

	private:
		ImGuiIO* m_IO = nullptr;
		float m_Time = 0.0f;
	};
}
