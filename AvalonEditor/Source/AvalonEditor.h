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

		std::unique_ptr<Avalon::Entity> entity1;
		std::unique_ptr<Avalon::Entity> entity2;
		std::unique_ptr<Avalon::Entity> entity3;

		std::unique_ptr<Avalon::QuadComponent> quadComponent1;
		std::unique_ptr<Avalon::QuadComponent> quadComponent2;
		std::unique_ptr<Avalon::QuadComponent> quadComponent3;

		std::unique_ptr<Avalon::VerticalMovementComponent> vmComp;

		Vec4 mSquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
		Vec3 mSquarePosition = { 0.0f, 0.0f, 0.1f };
		Vec2 mViewportSize = { 0.0f, 0.0f };

		bool mViewportFocused;
		bool mViewportHovered;
	};
}