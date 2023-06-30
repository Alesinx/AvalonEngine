#include "AvalonPch.h"
#include "ImguiOverlay.h"
#include "Avalon/Core/Application.h"

#define IMGUI_IMPL_OPENGL_LOADER_GLAD
#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_glfw.h"

#include "imgui.h"

// TEMPORARY
#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Avalon
{
	void ImguiOverlay::Initialize()
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGui::StyleColorsDark();

		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
		//io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
		//io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoTaskBarIcons;
		//io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoMerge;
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		//io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		//io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;
		
		// Setup Platform/Renderer bindings
		Application& app = Application::GetInstance();
		GLFWwindow* window = static_cast<GLFWwindow*>(app.GetWindow().GetNativeWindow());
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		
		ImGui_ImplOpenGL3_Init("#version 410");
	}

	void ImguiOverlay::Begin()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	void ImguiOverlay::Render()
	{
		if (showDemo)
		{
			static bool open;
			ImGui::ShowDemoWindow(&open);
		}
	}

	void ImguiOverlay::End()
	{
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		ImGuiIO& io = ImGui::GetIO();
		Application& app = Application::GetInstance();
		io.DisplaySize = ImVec2(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());

		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}
	}
}
