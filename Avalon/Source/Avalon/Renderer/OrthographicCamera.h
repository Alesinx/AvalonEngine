#pragma once

namespace Avalon
{
	class OrthographicCamera
	{
	public:
		OrthographicCamera(float left, float right, float bottom, float top);

		void SetProjection(float left, float right, float bottom, float top);

		inline const Vec3 GetPosition() const { return mPosition; }
		void SetPosition(const Vec3 position) { mPosition = position; RecalculateViewMatrix(); }

		inline const float GetRotation() const { return mRotation; }
		void SetRotation(const float rotation) { mRotation = rotation; RecalculateViewMatrix(); }

		const Mat4 GetProjectionMatrix() const { return mProjectionMatrix; }
		const Mat4 GetViewMatrix() const { return mViewMatrix; }
		const Mat4 GetViewProjecionMatrix() const { return mViewProjectionMatrix; }

	private:
		void RecalculateViewMatrix();

	private:
		Mat4 mProjectionMatrix;
		Mat4 mViewMatrix;
		Mat4 mViewProjectionMatrix;

		Vec3 mPosition = { 0.0f, 0.0f, 0.0f };
		float mRotation = 0.0f;

		// I think I shoudl not do this
		const Vec2 GetPosition2D() { return Vec2(mPosition[0], mPosition[1]); }
	};
}
