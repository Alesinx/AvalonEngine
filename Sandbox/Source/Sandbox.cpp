#include "Sandbox.h"

Avalon::Application* Avalon::CreateApplication()
{
	AVALON_INFO("Creating 'Sandbox' application...");

	//int one = 1;
	//int two = 2;
	//int three = 3;
	//AVALON_INFO("Test AVALON_INFO: {0}, {1}, {2}", 1, two, three);
	//AVALON_TRACE("Test AVALON_TRACE: {0}, {1}, {2}", one, two, three);
	//AVALON_WARNING("Test AVALON_WARNING: {0}, {1}, {2}", one, two, three);
	//AVALON_ERROR("Test AVALON_ERROR: {0}, {1}, {2}", one, two, three);

	//const std::string path = "C:/dev/AvalonEngine/";
	//const std::string fileName = "Example.txt";
	//const std::string contentToWrite = "Lorem ipsum dolor sit amet";
	//std::string contentRead;

	//AVALON_CORE_INFO("[File read/write test]");
	//AVALON_CORE_INFO("Writing on file {}{}", path, fileName);

	//const int FileWriteOutCode = FileIO::WriteFile(contentToWrite, path, fileName);
	//const int FileReadOutCode = FileIO::ReadFile(contentRead, path, fileName);

	//if (FileReadOutCode != FileIO::Ok)
	//	AVALON_CORE_ERROR("Could not read file");
	//else
	//	AVALON_CORE_INFO("This is what's inside of {}{}: {}", path, fileName, contentRead);

	return new Sandbox();
}

void Sandbox::SetupTriangle()
{
	mTriangleVA = Avalon::VertexArray::Create();

	const float vertices[3 * 7] = {
		// Position  | Color
		-0.5f, -0.5f, 0.8f, 0.2f, 0.8f, 1.0f,
		 0.5f, -0.5f, 0.2f, 0.3f, 0.8f, 1.0f,
		 0.0f,  0.5f, 0.8f, 0.8f, 0.2f, 1.0f
	};

	std::shared_ptr<Avalon::VertexBuffer> vb = Avalon::VertexBuffer::Create(vertices, sizeof(vertices));
	vb->SetLayout(
		{
			{ Avalon::ShaderDataType::Float2, "a_position" },
			{ Avalon::ShaderDataType::Float4, "a_color"}
		}
	);
	mTriangleVA->AddVertexBuffer(vb);

	const uint32_t indices[3] = { 0, 1, 2 };
	std::shared_ptr<Avalon::IndexBuffer> ib = Avalon::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
	mTriangleVA->SetIndexBuffer(ib);

	std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec2 a_position;
			layout(location = 1) in vec4 a_color;

			uniform mat4 u_ViewProjection;

			out vec2 v_position;
			out vec4 v_color;

			void main()
			{
				v_position = a_position;
				v_color = a_color;
				gl_Position = u_ViewProjection * vec4(a_position, 1.0, 1.0);
			}
		)";

	std::string fragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec2 v_position;
			in vec4 v_color;

			void main()
			{
				//color = vec4(v_position * 0.5 + 0.5, 1.0, 1.0);
				color = v_color;
			}
		)";

	std::shared_ptr<Avalon::Shader> triangleShader = Avalon::Shader::Create("triangleShader", vertexSrc, fragmentSrc);
	mShaderLibrary.Add("TriangleShader", triangleShader);
}

void Sandbox::SetupGrid()
{
	mSquareVA = Avalon::VertexArray::Create();

	float squareVertices[4 * 4] = {
		-0.5f,  0.5f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.0f,  0.0f,
		 0.5f, -0.5f,  1.0f,  0.0f,
		 0.5f,  0.5f,  1.0f,  1.0f
	};

	std::shared_ptr<Avalon::VertexBuffer> squareVB = Avalon::VertexBuffer::Create(squareVertices, sizeof(squareVertices));
	squareVB->SetLayout(
		{
			{ Avalon::ShaderDataType::Float2, "a_position" },
			{ Avalon::ShaderDataType::Float2, "a_TexCoord" }
		}
	);
	mSquareVA->AddVertexBuffer(squareVB);

	const uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
	std::shared_ptr<Avalon::IndexBuffer> squareIB = Avalon::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
	mSquareVA->SetIndexBuffer(squareIB);

	std::string blueShaderVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec2 a_position;

			uniform mat4 u_Transform;
			uniform mat4 u_ViewProjection;

			out vec2 v_position;

			void main()
			{
				v_position = a_position;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_position, 1.0, 1.0);
			}
		)";

	std::string blueShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			void main()
			{
				color = vec4(0.2, 0.3, 0.8, 1.0);
			}
		)";

	std::shared_ptr<Avalon::Shader> blueShader = Avalon::Shader::Create("BlueShader", blueShaderVertexSrc, blueShaderFragmentSrc);
	mShaderLibrary.Add("BlueShader", blueShader);
}

void Sandbox::SetupTextures()
{
	mTextureShader = mShaderLibrary.Load("Texture", "C:\\dev\\Avalon\\Sandbox\\Asset\\Shaders\\Texture.glsl");

	//mTexture = Avalon::Texture2D::Create("C:\\Dev\\AvalonEngine\\Avalon\\Assets\\Textures\\Checkerboard.png");
	mTexture = Avalon::Texture2D::Create("C:\\dev\\Avalon\\Avalon\\Assets\\Textures\\Checkerboard.png");
	
	//mFishTexture = Avalon::Texture2D::Create("C:\\Dev\\AvalonEngine\\Avalon\\Assets\\Textures\\Fish.png");
	mFishTexture = Avalon::Texture2D::Create("C:\\dev\\Avalon\\Avalon\\Assets\\Textures\\Fish.png");

	const std::shared_ptr<Avalon::OpenGLShader> openglTextureShader = std::dynamic_pointer_cast<Avalon::OpenGLShader>(mTextureShader);
	openglTextureShader->Bind();
	openglTextureShader->UploadUniformInt("u_Texture", 0);
}

void Sandbox::DrawGrid()
{
	std::shared_ptr<Avalon::Shader> blueShader = mShaderLibrary.Get("BlueShader");
	AVALON_ASSERT(blueShader, "Could not get blue shader");

	Mat4 scale = glm::scale(Mat4(1.0f), Vec3(0.1f));
	for (int y = 0; y < 20; y++)
	{
		for (int x = 0; x < 20; x++)
		{
			Vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
			Mat4 transform = glm::translate(Mat4(1.0f), pos) * scale;
			Avalon::Renderer::Submit(blueShader, mSquareVA, transform);
		}
	}
}

Sandbox::Sandbox() : mCameraController(1280.0f / 720.0f)
{
	mOverlayEnabled = false;

	SetupTriangle();
	SetupGrid();
	SetupTextures();
}

void Sandbox::ProcessEvent(Avalon::Event& event)
{
	Application::ProcessEvent(event);

	if (event.GetEventType() == Avalon::EventType::EventType_KeyPressed)
	{
		Avalon::KeyPressedEvent& e = static_cast<Avalon::KeyPressedEvent&>(event);
		if (e.GetKeyCode() == AVALON_KEY_TAB)
		{
			AVALON_TRACE("Tab key is pressed (event)");
		}
		int keycode = e.GetKeyCode();
		AVALON_TRACE("keycode {0} : {0}", static_cast<char>(keycode));
	}
	
	mCameraController.ProcessEvent(event);
}

void Sandbox::Update(float deltaTime)
{
	Application::Update(deltaTime);

	mCameraController.Update(deltaTime);
}

void Sandbox::Render(float deltaTime)
{
	Application::Render(deltaTime);

	Avalon::Renderer::BeginScene(mCameraController.GetCamera());

	DrawGrid();

	// Render blue quad
	//Renderer::Submit(mBlueShader, mSquareVA);

	// Render triangle
	//std::shared_ptr<Avalon::Shader> triangleShader = mShaderLibrary.Get("TriangleShader");
	//if (triangleShader)
	//	Avalon::Renderer::Submit(triangleShader, mTriangleVA);
	//else
	//	AVALON_ERROR("Tried to get triangle shader but it was null");

	// Render texture
	mTexture->Bind();
	Avalon::Renderer::Submit(mTextureShader, mSquareVA);

	mFishTexture->Bind();
	Avalon::Renderer::Submit(mTextureShader, mSquareVA);

	Avalon::Renderer::EndScene();
}
