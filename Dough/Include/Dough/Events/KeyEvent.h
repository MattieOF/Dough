#pragma once

#include "Dough/Events/Event.h"

namespace Dough
{
	class DOUGH_API KeyPressedEvent : public Dough::Event
	{
	public:
		KeyPressedEvent(int keycode, int repeatCount)
			: m_KeyCode(keycode), m_RepeatCount(repeatCount)
		{ }

		EVENT_CLASS_CATEGORY(EC_Keyboard | EC_Input)
		EVENT_CLASS_TYPE(KeyPressed)

		[[nodiscard]] inline int GetRepeatCount() const { return m_RepeatCount; }

		[[nodiscard]] std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_KeyCode << " (" << m_RepeatCount << " repeats)";
			return ss.str();
		}

	protected:
		int m_KeyCode;
		int m_RepeatCount;
	};

	class DOUGH_API KeyReleasedEvent : public Dough::Event
	{
	public:
		KeyReleasedEvent(int keycode)
			: m_KeyCode(keycode)
		{ }

		EVENT_CLASS_CATEGORY(EC_Keyboard | EC_Input)
		EVENT_CLASS_TYPE(KeyReleased)

		[[nodiscard]] std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << m_KeyCode;
			return ss.str();
		}

	protected:
		int m_KeyCode;
	};
}
