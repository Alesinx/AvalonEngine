#include <Avalon.h>
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
	mCheckerboardTexture = Avalon::Texture2D::Create("Assets/Textures/Checkerboard.png");
}

void Sandbox2D::Update(float deltaTime)
{
	Application::Update(deltaTime);

	mCameraController.Update(deltaTime);
}

void Sandbox2D::Render(float deltaTime)
{
	Application::Render(deltaTime);

	Avalon::Renderer::SetClearColor();
	Avalon::Renderer::Clear();
	
	Avalon::Renderer2D::BeginScene(mCameraController.GetCamera());
	Avalon::Renderer2D::DrawQuad(mSquarePosition, { 0.5f, 0.5f }, mSquareColor);
	Avalon::Renderer2D::DrawQuad({ 0.0f, 0.0f }, { 1.0f, 1.0f }, { 0.8f, 0.2f, 0.3f, 1.0f });
	Avalon::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 10.0f, 10.0f }, mCheckerboardTexture, Vec4(0.5f));
	Avalon::Renderer2D::EndScene();
}

void Sandbox2D::ImguiRender()
{
	Application::ImguiRender();

	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(mSquareColor));
	ImGui::SliderFloat("X", &mSquarePosition.x, -10, 10);
	ImGui::SliderFloat("Y", &mSquarePosition.y, -10, 10);
	ImGui::End();
}

void Sandbox2D::ProcessEvent(Avalon::Event& e)
{
	Application::ProcessEvent(e);

	mCameraController.ProcessEvent(e);
}
