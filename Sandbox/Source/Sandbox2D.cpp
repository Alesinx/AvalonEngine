#include "Sandbox2D.h"
#include <glm/gtc/type_ptr.hpp>
#include "imgui/imgui.h"

Avalon::Application* Avalon::CreateApplication()
{
	AVALON_INFO("Creating 'Sandbox2D' application...");
	return new Sandbox2D();
}

Sandbox2D::Sandbox2D() :
	mCameraController(1280.0f / 720.0f)
{
	mCheckerboardTexture = Avalon::Texture2D::Create("C:\\dev\\Avalon\\Avalon\\Assets\\Textures\\Checkerboard.png");
}

void Sandbox2D::Update(float deltaTime)
{
	Application::Update(deltaTime);

	mCameraController.Update(deltaTime);
}

void Sandbox2D::Render(float deltaTime)
{
	Application::Render(deltaTime);
	
	Avalon::Renderer2D::BeginScene(mCameraController.GetCamera());
	Avalon::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
	Avalon::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
	Avalon::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 10.0f, 10.0f }, mCheckerboardTexture);
	Avalon::Renderer2D::EndScene();
}

void Sandbox2D::ImguiRender()
{
	Application::ImguiRender();

	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(mSquareColor));
	ImGui::End();
}

void Sandbox2D::ProcessEvent(Avalon::Event& e)
{
	Application::ProcessEvent(e);

	mCameraController.ProcessEvent(e);
}
