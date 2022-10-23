#pragma once

#include "dhpch.h"
#include "Dough/Events/Event.h"

namespace Dough
{
	class DOUGH_API Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() { }
		virtual void OnDetach() { }
		virtual void OnUpdate() { }
		virtual void OnEvent(Event& event) { }

		[[nodiscard]] inline const std::string& GetName() const { return m_DebugName; }
	private:
		std::string m_DebugName;
	};
}
