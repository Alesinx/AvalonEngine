#include <Avalon.h>
#include <Avalon/Core/EntryPoint.h>

namespace Avalon
{
	class AvalonEditor : public Application
	{
	public:
		AvalonEditor();
		virtual ~AvalonEditor() = default;

		void Update(float deltaTime) override;
		void Render(float deltaTime) override;
		void ImguiRender(float deltaTime) override;
		void ProcessEvent(Event& e) override;

	private:
		OrthographicCameraController mCameraController;

		// Temp
		std::shared_ptr<VertexArray> mSquareVA;
		std::shared_ptr<Shader> mFlatColorShader;
		std::shared_ptr<Framebuffer> mFramebuffer;

		std::shared_ptr<Texture2D> mCheckerboardTexture;
		std::shared_ptr<Texture2D> mFishTexture;

		std::unique_ptr<Avalon::ExampleScene> exampleScene;

		Vec4 mSquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
		Vec3 mImguiPosition = { 0.0f, 0.0f, -0.1f };
		Vec2 mViewportSize = { 0.0f, 0.0f };

		bool mViewportFocused;
		bool mViewportHovered;

		float timeBetweenInfoUpdates = 1.0f;

		float fpsCounter = 0.0f;
		float lastInfoUpdateTime = 0.0f;
	};
}