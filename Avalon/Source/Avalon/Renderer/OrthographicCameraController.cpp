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
	if (Avalon::Input::IsKeyPressed(AVALON_KEY_D))
		mCameraPosition.x += offset;
	else if (Avalon::Input::IsKeyPressed(AVALON_KEY_A))
		mCameraPosition.x -= offset;

	if (Avalon::Input::IsKeyPressed(AVALON_KEY_W))
		mCameraPosition.y += offset;
	else if (Avalon::Input::IsKeyPressed(AVALON_KEY_S))
		mCameraPosition.y -= offset;

	mCamera.SetPosition(mCameraPosition);

	if (mRotation)
	{
		if (Avalon::Input::IsKeyPressed(AVALON_KEY_Q))
			mCameraRotation += mCameraRotationSpeed * deltaTime;
		else if (Avalon::Input::IsKeyPressed(AVALON_KEY_E))
			mCameraRotation -= mCameraRotationSpeed * deltaTime;

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
