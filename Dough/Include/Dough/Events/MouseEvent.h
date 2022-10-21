#pragma once

#include "Dough/Events/Event.h"

#include <sstream>

namespace Dough
{
	class DOUGH_API MouseMovedEvent : public Event
	{
	public:
		MouseMovedEvent(int x, int y)
			: m_MouseX(x), m_MouseY(y)
		{}

		EVENT_CLASS_CATEGORY(EC_Mouse | EC_Input)
		EVENT_CLASS_TYPE(MouseMoved)

		[[nodiscard]] inline int GetX() const { return m_MouseX; }
		[[nodiscard]] inline int GetY() const { return m_MouseY; }

		[[nodiscard]] std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseMovedEvent: " << m_MouseX << ", " << m_MouseY;
			return ss.str();
		}

	private:
		int m_MouseX, m_MouseY;
	};

	class DOUGH_API MouseScrolledEvent : public Event
	{
	public:
		MouseScrolledEvent(int xOffset, int yOffset)
			: m_XOffset(xOffset), m_YOffset(yOffset)
		{}

		EVENT_CLASS_CATEGORY(EC_Mouse | EC_Input)
		EVENT_CLASS_TYPE(MouseScrolled)

		[[nodiscard]] inline int GetXOffset() const { return m_XOffset; }
		[[nodiscard]] inline int GetYOffset() const { return m_YOffset; }

		[[nodiscard]] std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseMovedEvent: " << m_XOffset << ", " << m_YOffset;
			return ss.str();
		}

	private:
		int m_XOffset, m_YOffset;
	};

	class DOUGH_API MouseButtonPressedEvent : public Event
	{
	public:
		MouseButtonPressedEvent(int button)
			: m_Button(button)
		{}

		EVENT_CLASS_CATEGORY(EC_Mouse | EC_Input)
		EVENT_CLASS_TYPE(MouseButtonPressed)

		[[nodiscard]] inline int GetButton() const { return m_Button; }

		[[nodiscard]] std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonPressedEvent: " << m_Button;
			return ss.str();
		}

	private:
		int m_Button;
	};

	class DOUGH_API MouseButtonReleasedEvent : public Event
	{
	public:
		MouseButtonReleasedEvent(int button)
			: m_Button(button)
		{}

		EVENT_CLASS_CATEGORY(EC_Mouse | EC_Input)
		EVENT_CLASS_TYPE(MouseButtonReleased)

		[[nodiscard]] inline int GetButton() const { return m_Button; }

		[[nodiscard]] std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonReleasedEvent: " << m_Button;
			return ss.str();
		}

	private:
		int m_Button;
	};
}
