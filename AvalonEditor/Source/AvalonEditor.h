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
		void ImguiRender() override;
		void ProcessEvent(Event& e) override;

	private:
		OrthographicCameraController mCameraController;

		// Temp
		std::shared_ptr<VertexArray> mSquareVA;
		std::shared_ptr<Shader> mFlatColorShader;
		std::shared_ptr<Framebuffer> mFramebuffer;

		std::shared_ptr<Texture2D> mCheckerboardTexture;

		Vec4 mSquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
		Vec2 mSquarePosition = { 0.0f, 0.0f };
		Vec2 mViewportSize = { 0.0f, 0.0f };

		bool mViewportFocused;
		bool mViewportHovered;
	};
}