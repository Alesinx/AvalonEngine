#include <Avalon.h>
#include "AvalonEditor.h"
#include <glm/gtc/type_ptr.hpp>
#include <imgui/imgui.h>

namespace Avalon
{
	Application* CreateApplication()
	{
		return new AvalonEditor();
	}

	AvalonEditor::AvalonEditor() :
		Application("Avalon Editor"),
		mCameraController(1280.0f / 720.0f)
	{
		mCheckerboardTexture = Avalon::Texture2D::Create("Assets/Textures/Checkerboard.png");

		Avalon::FramebufferSpecification fbSpec;
		fbSpec.width = 1280;
		fbSpec.height = 720;
		mFramebuffer = Avalon::Framebuffer::Create(fbSpec);
	}

	void AvalonEditor::Update(float deltaTime)
	{
		Application::Update(deltaTime);

		mCameraController.Update(deltaTime);
	}

	void AvalonEditor::Render(float deltaTime)
	{
		Application::Render(deltaTime);

		mFramebuffer->Bind();

		Avalon::Renderer::SetClearColor();
		Avalon::Renderer::Clear();

		Avalon::Renderer2D::BeginScene(mCameraController.GetCamera());
		Avalon::Renderer2D::DrawQuad(mSquarePosition, { 0.5f, 0.5f }, mSquareColor);
		Avalon::Renderer2D::DrawQuad({ 0.0f, 0.0f }, { 1.0f, 1.0f }, { 0.8f, 0.2f, 0.3f, 1.0f });
		Avalon::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 10.0f, 10.0f }, mCheckerboardTexture, Vec4(0.5f));
		Avalon::Renderer2D::EndScene();

		mFramebuffer->Unbind();
	}

	void AvalonEditor::ImguiRender()
	{
		Application::ImguiRender();

		static bool dockspaceOpen = true;
		static bool opt_fullscreen_persistant = true;
		static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

		bool opt_fullscreen = opt_fullscreen_persistant;

		// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
		// because it would be confusing to have two docking targets within each others.
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
		if (opt_fullscreen)
		{
			ImGuiViewport* viewport = ImGui::GetMainViewport();
			ImGui::SetNextWindowPos(viewport->Pos);
			ImGui::SetNextWindowSize(viewport->Size);
			ImGui::SetNextWindowViewport(viewport->ID);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
			window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
			window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
		}

		// When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background and handle the pass-thru hole, so we ask Begin() to not render a background.
		if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
			window_flags |= ImGuiWindowFlags_NoBackground;

		// Important: note that we proceed even if Begin() returns false (aka window is collapsed).
		// This is because we want to keep our DockSpace() active. If a DockSpace() is inactive, 
		// all active windows docked into it will lose their parent and become undocked.
		// We cannot preserve the docking relationship between an active window and an inactive docking, otherwise 
		// any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

		ImGui::Begin("DockSpace Demo", &dockspaceOpen, window_flags);
		ImGui::PopStyleVar();

		if (opt_fullscreen)
			ImGui::PopStyleVar(2);

		// DockSpace
		ImGuiIO& io = ImGui::GetIO();
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
		}

		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				// Disabling fullscreen would allow the window to be moved to the front of other windows, 
				// which we can't undo at the moment without finer window depth/z control.
				//ImGui::MenuItem("Fullscreen", NULL, &opt_fullscreen_persistant);

				if (ImGui::MenuItem("Exit")) Avalon::Application::GetInstance().Close();
				ImGui::EndMenu();
			}

			ImGui::EndMenuBar();
		}

		// Viewport
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });
		ImGui::Begin("Viewport");
		mViewportFocused = ImGui::IsWindowFocused();
		mViewportHovered = ImGui::IsWindowHovered();
		mCameraController.SetPollEvents(mViewportFocused || mViewportHovered);
		ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
		if (mViewportSize.x != viewportPanelSize.x || mViewportSize.y != viewportPanelSize.y)
		{
			mFramebuffer->Resize((uint32_t)viewportPanelSize.x, (uint32_t)viewportPanelSize.y);
			mViewportSize = { viewportPanelSize.x, viewportPanelSize.y };
			mCameraController.Resize(viewportPanelSize.x, viewportPanelSize.y);
		}
		uint32_t viewportTextureID = mFramebuffer->GetColorAttachmentRendererID();
		ImGui::Image((void*)viewportTextureID, ImVec2{ (float)mViewportSize.x, (float)mViewportSize.y }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });
		ImGui::End();
		ImGui::PopStyleVar();

		// Settings
		ImGui::Begin("Settings");
		ImGui::ColorEdit4("Square Color", glm::value_ptr(mSquareColor));
		ImGui::SliderFloat("X", &mSquarePosition.x, -10, 10);
		ImGui::SliderFloat("Y", &mSquarePosition.y, -10, 10);
		ImGui::End();

		// Hierarchy
		ImGui::Begin("Scene hierarchy");
		ImGui::End();

		// Console
		ImGui::Begin("Console");
		ImGui::End();

		ImGui::End(); // Dockspace
	}

	void AvalonEditor::ProcessEvent(Avalon::Event& e)
	{
		Application::ProcessEvent(e);

		if(mViewportFocused || mViewportHovered)
		{
			mCameraController.ProcessEvent(e);
		}
	}
}