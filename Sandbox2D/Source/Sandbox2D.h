#pragma once

#include <Avalon.h>
#include <Avalon/Core/EntryPoint.h>

class Sandbox2D : public Avalon::Application
{
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	void Update(float deltaTime) override;
	void Render(float deltaTime) override;
	void ImguiRender() override;
	void ProcessEvent(Avalon::Event& e) override;

private:
	Avalon::OrthographicCameraController mCameraController;

	// Temp
	std::shared_ptr<Avalon::VertexArray> mSquareVA;
	std::shared_ptr<Avalon::Shader> mFlatColorShader;
	std::shared_ptr<Avalon::Framebuffer> mFramebuffer;

	std::shared_ptr<Avalon::Texture2D> mCheckerboardTexture;

	std::unique_ptr<Avalon::Entity> entity1;
	std::unique_ptr<Avalon::Entity> entity2;
	std::unique_ptr<Avalon::Entity> entity3;

	std::unique_ptr<Avalon::QuadComponent> quadComponent1;
	std::unique_ptr<Avalon::QuadComponent> quadComponent2;
	std::unique_ptr<Avalon::QuadComponent> quadComponent3;

	Vec4 mSquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
	Vec2 mSquarePosition = { 0.0f, 0.0f };
};