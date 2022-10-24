#include "dhpch.h"
#include "Dough/ImGui/ImGuiLayer.h"

#include "imgui.h"
#include "Dough/Core/Application.h"
#include "Dough/Platform/OpenGL/imgui_impl_opengl3.h"
#include "GLFW/glfw3.h"

namespace Dough
{
	ImGuiLayer::ImGuiLayer()
		: Layer("ImGui Layer")
	{
	}

	ImGuiLayer::~ImGuiLayer()
	{
	}

	void ImGuiLayer::OnAttach()
	{
		Layer::OnAttach();
		
		ImGui::CreateContext();
		ImGui::StyleColorsDark();

		m_IO = &ImGui::GetIO();
		m_IO->BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		m_IO->BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

		// TEMPORARY: should eventually use Dough key codes
		m_IO->KeyMap[ImGuiKey_Tab] = GLFW_KEY_TAB;
		m_IO->KeyMap[ImGuiKey_LeftArrow] = GLFW_KEY_LEFT;
		m_IO->KeyMap[ImGuiKey_RightArrow] = GLFW_KEY_RIGHT;
		m_IO->KeyMap[ImGuiKey_UpArrow] = GLFW_KEY_UP;
		m_IO->KeyMap[ImGuiKey_DownArrow] = GLFW_KEY_DOWN;
		m_IO->KeyMap[ImGuiKey_PageUp] = GLFW_KEY_PAGE_UP;
		m_IO->KeyMap[ImGuiKey_PageDown] = GLFW_KEY_PAGE_DOWN;
		m_IO->KeyMap[ImGuiKey_Home] = GLFW_KEY_HOME;
		m_IO->KeyMap[ImGuiKey_End] = GLFW_KEY_END;
		m_IO->KeyMap[ImGuiKey_Insert] = GLFW_KEY_INSERT;
		m_IO->KeyMap[ImGuiKey_Delete] = GLFW_KEY_DELETE;
		m_IO->KeyMap[ImGuiKey_Backspace] = GLFW_KEY_BACKSPACE;
		m_IO->KeyMap[ImGuiKey_Space] = GLFW_KEY_SPACE;
		m_IO->KeyMap[ImGuiKey_Enter] = GLFW_KEY_ENTER;
		m_IO->KeyMap[ImGuiKey_Escape] = GLFW_KEY_ESCAPE;
		m_IO->KeyMap[ImGuiKey_A] = GLFW_KEY_A;
		m_IO->KeyMap[ImGuiKey_C] = GLFW_KEY_C;
		m_IO->KeyMap[ImGuiKey_V] = GLFW_KEY_V;
		m_IO->KeyMap[ImGuiKey_X] = GLFW_KEY_X;
		m_IO->KeyMap[ImGuiKey_Y] = GLFW_KEY_Y;
		m_IO->KeyMap[ImGuiKey_Z] = GLFW_KEY_Z;

		ImGui_ImplOpenGL3_Init("#version 410");

		Application& app = Application::Get();
		m_IO->DisplaySize = ImVec2(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());

		// Setup clipboard
		m_IO->ClipboardUserData = &app.GetWindow();
		m_IO->SetClipboardTextFn = SetClipboardTextCallback;
		m_IO->GetClipboardTextFn = GetClipboardTextCallback;
	}

	void ImGuiLayer::OnDetach()
	{
		Layer::OnDetach();

		ImGui_ImplOpenGL3_Shutdown();
	}

	void ImGuiLayer::OnUpdate()
	{
		Layer::OnUpdate();
		
		float time = static_cast<float>(glfwGetTime());
		m_IO->DeltaTime = m_Time > 0.0f ? (time - m_Time) : (1.0f / 60.0f);
		m_Time = time;

		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();
		
		static bool open = true;
		ImGui::ShowDemoWindow(&open);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void ImGuiLayer::OnEvent(Event& event)
	{
		Layer::OnEvent(event);

		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<MouseMovedEvent>(BIND_EVENT_FN(ImGuiLayer::OnMouseMoved));
		dispatcher.Dispatch<MouseButtonPressedEvent>(BIND_EVENT_FN(ImGuiLayer::OnMouseButtonDown));
		dispatcher.Dispatch<MouseButtonReleasedEvent>(BIND_EVENT_FN(ImGuiLayer::OnMouseButtonUp));
		dispatcher.Dispatch<MouseScrolledEvent>(BIND_EVENT_FN(ImGuiLayer::OnMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(ImGuiLayer::OnWindowResize));
		dispatcher.Dispatch<KeyTypedEvent>(BIND_EVENT_FN(ImGuiLayer::OnKeyTyped));
		dispatcher.Dispatch<KeyPressedEvent>(BIND_EVENT_FN(ImGuiLayer::OnKeyPressed));
		dispatcher.Dispatch<KeyReleasedEvent>(BIND_EVENT_FN(ImGuiLayer::OnKeyReleased));
	}

	bool ImGuiLayer::OnMouseMoved(MouseMovedEvent& e) const
	{
		m_IO->MousePos = ImVec2(e.GetX(), e.GetY());
		return false;
	}

	bool ImGuiLayer::OnMouseButtonDown(MouseButtonPressedEvent& e) const
	{
		m_IO->AddMouseButtonEvent(e.GetButton(), true);
		return false;
	}

	bool ImGuiLayer::OnMouseButtonUp(MouseButtonReleasedEvent& e) const
	{
		m_IO->AddMouseButtonEvent(e.GetButton(), false);
		return false;
	}

	bool ImGuiLayer::OnMouseScrolled(MouseScrolledEvent& e) const
	{
		m_IO->AddMouseWheelEvent(e.GetXOffset(), e.GetYOffset());
		return false;
	}

	bool ImGuiLayer::OnKeyPressed(KeyPressedEvent& e) const
	{
		m_IO->KeysDown[e.GetKeyCode()] = true;

		m_IO->KeyCtrl = m_IO->KeysDown[GLFW_KEY_LEFT_CONTROL] || m_IO->KeysDown[GLFW_KEY_RIGHT_CONTROL];
		m_IO->KeyShift = m_IO->KeysDown[GLFW_KEY_LEFT_SHIFT] || m_IO->KeysDown[GLFW_KEY_RIGHT_SHIFT];
		m_IO->KeyAlt = m_IO->KeysDown[GLFW_KEY_LEFT_ALT] || m_IO->KeysDown[GLFW_KEY_RIGHT_ALT];
		m_IO->KeySuper = m_IO->KeysDown[GLFW_KEY_LEFT_SUPER] || m_IO->KeysDown[GLFW_KEY_RIGHT_SUPER];

		return false;
	}

	bool ImGuiLayer::OnKeyReleased(KeyReleasedEvent& e) const
	{
		m_IO->KeysDown[e.GetKeyCode()] = false;

		m_IO->KeyCtrl = m_IO->KeysDown[GLFW_KEY_LEFT_CONTROL] || m_IO->KeysDown[GLFW_KEY_RIGHT_CONTROL];
		m_IO->KeyShift = m_IO->KeysDown[GLFW_KEY_LEFT_SHIFT] || m_IO->KeysDown[GLFW_KEY_RIGHT_SHIFT];
		m_IO->KeyAlt = m_IO->KeysDown[GLFW_KEY_LEFT_ALT] || m_IO->KeysDown[GLFW_KEY_RIGHT_ALT];
		m_IO->KeySuper = m_IO->KeysDown[GLFW_KEY_LEFT_SUPER] || m_IO->KeysDown[GLFW_KEY_RIGHT_SUPER];

		return false;
	}

	bool ImGuiLayer::OnKeyTyped(KeyTypedEvent& e) const
	{
		const int keycode = e.GetKeyCode();
		if (keycode > 0 && keycode < 0x10000)
			m_IO->AddInputCharacter(keycode);

		return false;
	}

	bool ImGuiLayer::OnWindowResize(WindowResizeEvent& e) const
	{
		m_IO->DisplaySize = ImVec2(e.GetWidth(), e.GetHeight());
		return false;
	}

	const char* ImGuiLayer::GetClipboardTextCallback(void* userData)
	{
		const Window* window = static_cast<Window*>(userData);
		return window->GetClipboardText();
	}

	void ImGuiLayer::SetClipboardTextCallback(void* userData, const char* text)
	{
		Window* window = static_cast<Window*>(userData);
		window->SetClipboardText(text);
	}
}
