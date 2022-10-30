#pragma once

#include "dhpch.h"
#include "Dough/Core/Input/Input.h"

namespace Dough
{
	class WindowsInput : public Input
	{
	protected:
		virtual bool IsKeyPressedImpl(int keyCode) override;
		virtual bool IsMouseButtonPressedImpl(int button) override;
		virtual std::pair<double, double>& GetMousePosImpl() override;
	};
}
