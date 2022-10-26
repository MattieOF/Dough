#include "dhpch.h"
#include "Dough/ImGui/ImGuiLayer.h"

#include "imgui.h"
#include "Dough/Core/Application.h"
#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_glfw.h"
#include "GLFW/glfw3.h"

namespace Dough
{
	static bool s_ImGuiInitialised = false;

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

		DH_ASSERT_ERROR(!s_ImGuiInitialised, "Attached a new ImGuiLayer, but ImGui has already been initialised!");
		
		// Setup ImGui context
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		m_IO = &ImGui::GetIO();

		// Setup ImGui config
		m_IO->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		m_IO->ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
		m_IO->ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		m_IO->ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

		// Style ImGui
		ImGui::StyleColorsDark();

		// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
		ImGuiStyle& style = ImGui::GetStyle();
		if (m_IO->ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			// style.WindowRounding = 0.0f;
			style.WindowRounding = 5.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}

		// Setup Platform backends
		Application& app = Application::Get();
		GLFWwindow* window = static_cast<GLFWwindow*>(app.GetWindow().GetNativeWindow());
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init("#version 410");

		s_ImGuiInitialised = true;
	}

	void ImGuiLayer::OnDetach()
	{
		Layer::OnDetach();
		
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();

		s_ImGuiInitialised = false;
	}

	void ImGuiLayer::OnImGuiRender()
	{
		static bool show = true;
		ImGui::ShowDemoWindow(&show);
	}

	void ImGuiLayer::Begin()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	void ImGuiLayer::End()
	{
		// Setup display size
		Application& app = Application::Get();
		m_IO->DisplaySize = ImVec2(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());

		// Render
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		// Update viewports
		if (m_IO->ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backupCurrentContext = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backupCurrentContext);
		}
	}
}
