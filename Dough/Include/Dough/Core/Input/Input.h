#pragma once

#include "dhpch.h"

namespace Dough
{
	class DOUGH_API Input
	{
		friend class WindowsWindow;

	public:
		[[nodiscard]] inline static bool IsKeyPressed(int keyCode) { return s_Instance->IsKeyPressedImpl(keyCode); }
		[[nodiscard]] inline static bool IsKeyReleased(int keyCode) { return !(s_Instance->IsKeyPressedImpl(keyCode)); }
		[[nodiscard]] inline static bool IsMouseButtonPressed(int button) { return s_Instance->IsMouseButtonPressedImpl(button); }
		[[nodiscard]] inline static bool IsMouseButtonReleased (int button) { return !(s_Instance->IsMouseButtonPressedImpl(button)); }
		[[nodiscard]] inline static std::pair<float, float> GetMousePos() { return s_Instance->GetMousePosImpl(); }
	protected:
		virtual bool IsKeyPressedImpl(int keyCode) = 0;
		virtual bool IsMouseButtonPressedImpl(int button) = 0;
		virtual std::pair<double, double>& GetMousePosImpl() = 0;
	private:
		static Input* s_Instance;
	};
}
