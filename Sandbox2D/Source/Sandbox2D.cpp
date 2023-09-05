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

	entity1 = std::unique_ptr<Avalon::Entity>(new Avalon::Entity({ 0.f, 0.f, 0.1f }));
	entity2 = std::unique_ptr<Avalon::Entity>(new Avalon::Entity({ 0.f, 0.f, 0.2f }));
	entity3 = std::unique_ptr<Avalon::Entity>(new Avalon::Entity({ 0.f, 0.f, 0.3f }));

	quadComponent1 = std::unique_ptr<Avalon::QuadComponent>();
	quadComponent2 = std::unique_ptr<Avalon::QuadComponent>();
	quadComponent3 = std::unique_ptr<Avalon::QuadComponent>();

	entity1->AddComponent(quadComponent1.get());
	entity2->AddComponent(quadComponent2.get());
	entity3->AddComponent(quadComponent3.get());
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
	entity1->Render();
	entity2->Render();
	entity3->Render();
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
