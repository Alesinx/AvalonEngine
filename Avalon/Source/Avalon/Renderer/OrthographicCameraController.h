#pragma once

#include "Avalon/Renderer/OrthographicCamera.h"
#include "Avalon/Event/Event.h"
#include "Avalon/Event/ApplicationEvents.h"
#include "Avalon/Event/InputEvents/MouseEvents.h"

namespace Avalon
{
	class OrthographicCameraController
	{
	public:
		OrthographicCameraController(float aspectRation, bool rotation = false);

		void Update(float deltaTime);
		void ProcessEvent(Event& e);

		void Resize(float width, float height);

		OrthographicCamera& GetCamera() { return mCamera; }
		const OrthographicCamera& GetCamera() const { return mCamera; }

	private:
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);

	private:
		float mAspectRatio;
		float mZoomLevel = 1.0f;
		OrthographicCamera mCamera;
		bool mRotation;

		Vec3 mCameraPosition = { 0.0f, 0.0f, 0.0f };
		float mCameraRotation = 0.0f;
		float mCameraTranslationSpeed = 4.0f;
		float mCameraRotationSpeed = 180.0f;
	};
}
