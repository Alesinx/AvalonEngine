#include <Avalon.h>
#include <Avalon/Core/EntryPoint.h>

namespace Avalon
{
	enum class EditorState
	{
		Edit = 0,
		Play = 1,
		Pause = 2
	};

	class AvalonEditor : public Application
	{
	public:
		AvalonEditor();
		virtual ~AvalonEditor() = default;

		void Update(float deltaTime) override;
		void Render(float deltaTime) override;
		void ImguiRender(float deltaTime) override;
		void ProcessEvent(Event& e) override;

		void EditorUpdate(float deltaTime);
		void RuntimeUpdate(float deltaTime);

	private:
		void UpdateInfo(float deltaTime);
		void OnEditorPlay();
		void OnEditorStop();
		void RenderToolbar();

	private:
		OrthographicCameraController editorCameraController;

		// Temp
		std::shared_ptr<VertexArray> mSquareVA;
		std::shared_ptr<Shader> mFlatColorShader;
		std::shared_ptr<Framebuffer> mFramebuffer;

		std::shared_ptr<Texture2D> mCheckerboardTexture;
		std::shared_ptr<Texture2D> mFishTexture;

		Vec4 mSquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
		Vec3 mImguiPosition = { 0.0f, 0.0f, -0.1f };
		Vec2 mViewportSize = { 0.0f, 0.0f };

		bool mViewportFocused;
		bool mViewportHovered;

		float timeBetweenInfoUpdates = 1.0f;

		float fpsCounter = 0.0f;
		float lastInfoUpdateTime = 0.0f;

		EditorState state = EditorState::Edit;

		std::shared_ptr<Texture2D> editorPlayIcon;
		std::shared_ptr<Texture2D> editorStopIcon;
	};
}