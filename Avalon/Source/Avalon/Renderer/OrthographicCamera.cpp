#include "AvalonPch.h"
#include "OrthographicCamera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Avalon
{
	OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top) :
		mViewMatrix(1.0f)
	{
		SetProjection(left, right, bottom, top);
	}

	void OrthographicCamera::SetProjection(float left, float right, float bottom, float top)
	{
		mProjectionMatrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
		mViewProjectionMatrix = mProjectionMatrix * mViewMatrix;
	}

	void OrthographicCamera::RecalculateViewMatrix()
	{
		Mat4 transform = glm::translate(Mat4(1.0f), mPosition) * glm::rotate(Mat4(1.0f), glm::radians(mRotation), Vec3(0, 0, 1));
		mViewMatrix = glm::inverse(transform);

		mViewProjectionMatrix = mProjectionMatrix * mViewMatrix;
	}
}
