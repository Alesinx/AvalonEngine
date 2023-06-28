#include "AvalonPch.h"
#include "Avalon/Core/Core.h"
#include "OrthographicCameraController.h"
#include "Avalon/Input/Input.h"
#include "Avalon/Input/InputKeys.h"

Avalon::OrthographicCameraController::OrthographicCameraController(float aspectRation, bool rotation) : 
	mAspectRatio(aspectRation),
	mCamera(-mAspectRatio * mZoomLevel, mAspectRatio* mZoomLevel, -mZoomLevel, mZoomLevel),
	mRotation(rotation)
{
}

void Avalon::OrthographicCameraController::Update(float deltaTime)
{
	float offset = mCameraTranslationSpeed * mZoomLevel * deltaTime;
	float rotationRadians = glm::radians(mCameraRotation);

	if (Avalon::Input::IsKeyPressed(AVALON_KEY_D))
	{
		mCameraPosition.x += cos(rotationRadians) * offset;
		mCameraPosition.y += sin(rotationRadians) * offset;
	}
	else if (Avalon::Input::IsKeyPressed(AVALON_KEY_A))
	{
		mCameraPosition.x -= cos(rotationRadians) * offset;
		mCameraPosition.y -= sin(rotationRadians) * offset;
	}

	if (Avalon::Input::IsKeyPressed(AVALON_KEY_W))
	{
		mCameraPosition.x += -sin(rotationRadians) * offset;
		mCameraPosition.y += cos(rotationRadians) * offset;
	}
	else if (Avalon::Input::IsKeyPressed(AVALON_KEY_S))
	{
		mCameraPosition.x -= -sin(rotationRadians) * offset;
		mCameraPosition.y -= cos(rotationRadians) * offset;
	}

	mCamera.SetPosition(mCameraPosition);

	if (mRotation)
	{
		if (Avalon::Input::IsKeyPressed(AVALON_KEY_Q))
			mCameraRotation += mCameraRotationSpeed * deltaTime;
		else if (Avalon::Input::IsKeyPressed(AVALON_KEY_E))
			mCameraRotation -= mCameraRotationSpeed * deltaTime;

		if (mCameraRotation > 180.0f)
			mCameraRotation -= 360.0f;
		else if (mCameraRotation <= -180.0f)
			mCameraRotation += 360.0f;

		mCamera.SetRotation(mCameraRotation);
	}
}

void Avalon::OrthographicCameraController::ProcessEvent(Event& e)
{
	if (e.Dispatch<MouseScrolledEvent>(BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled)))
		return;
	if (e.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(OrthographicCameraController::OnWindowResized)))
		return;
}

bool Avalon::OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e)
{
	mZoomLevel -= e.GetYOffset() * 0.25f;
	mZoomLevel = std::max(mZoomLevel, 0.25f);
	mCamera.SetProjection(-mAspectRatio * mZoomLevel, mAspectRatio * mZoomLevel, -mZoomLevel, mZoomLevel);
	return false;
}

bool Avalon::OrthographicCameraController::OnWindowResized(WindowResizeEvent& e)
{
	mAspectRatio = (float)e.GetWidth() / (float)e.GetHeight();
	mCamera.SetProjection(-mAspectRatio * mZoomLevel, mAspectRatio * mZoomLevel, -mZoomLevel, mZoomLevel);
	return false;
}
