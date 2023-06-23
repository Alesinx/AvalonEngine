#pragma once
#include <Avalon.h>
#include <glm/gtc/matrix_transform.hpp>

class Sandbox : public Avalon::Application
{
public:
	Sandbox();
	~Sandbox() = default;

	void ProcessEvent(Avalon::Event& event) override;
	void Update(float deltaTime) override;
	void Render(float deltaTime) override;

private:
	void SetupTriangle();
	void SetupGrid();
	void SetupTextures();

	void DrawGrid();

private:
	std::shared_ptr<Avalon::Shader> mTriangleShader;
	std::shared_ptr<Avalon::VertexArray> mTriangleVA;

	std::shared_ptr<Avalon::Shader> mBlueShader;
	std::shared_ptr<Avalon::VertexArray> mSquareVA;

	std::shared_ptr<Avalon::Texture2D> mTexture, mFishTexture;
	std::shared_ptr<Avalon::Shader> mTextureShader;

	Avalon::OrthographicCamera mCamera;
	Vec3 mCameraPosition = Vec3(0.0f);
	float mCameraRotation = 0.0f;
	float mCameraMoveSpeed = 5.0f;
	float mCameraRotationSpeed = 180.0f;
};
