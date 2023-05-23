#include <Avalon.h>

class Sandbox : public Avalon::Application
{
public:
	Sandbox() { }
	~Sandbox() { }

	void ProcessEvent(Avalon::Event& event) override
	{
		Application::ProcessEvent(event);

		if (event.GetEventType() == Avalon::EventType::EventType_KeyPressed)
		{
			Avalon::KeyPressedEvent& e = static_cast<Avalon::KeyPressedEvent&>(event);
			if(e.GetKeyCode() == AVALON_KEY_TAB)
			{
				AVALON_TRACE("Tab key is pressed (event)");
			}
			int keycode = e.GetKeyCode();
			AVALON_TRACE("keycode {0} : {0}", static_cast<char>(keycode));
		}
	}

	void Update() override
	{
		Application::Update();

		//if(Avalon::Input::IsKeyPressed(AVALON_KEY_TAB))
		//{
		//	AVALON_TRACE("Tab key is pressed (polling)");
		//}
	}
};

Avalon::Application* Avalon::CreateApplication()
{
	AVALON_INFO("Creating application...");

	int one = 1;
	int two = 2;
	int three = 3;
	AVALON_INFO("Test AVALON_INFO: {0}, {1}, {2}", one, two, three);
	AVALON_TRACE("Test AVALON_TRACE: {0}, {1}, {2}", one, two, three);
	AVALON_WARNING("Test AVALON_WARNING: {0}, {1}, {2}", one, two, three);
	AVALON_ERROR("Test AVALON_ERROR: {0}, {1}, {2}", one, two, three);

	const std::string path = "C:/dev/AvalonEngine/";
	const std::string fileName = "Example.txt";
	const std::string contentToWrite = "Lorem ipsum dolor sit amet";
	std::string contentRead;

	AVALON_CORE_INFO("[File read/write test]");
	AVALON_CORE_INFO("Writing on file {}{}", path, fileName);

	const int FileWriteOutCode = FileIO::WriteFile(contentToWrite, path, fileName);
	const int FileReadOutCode = FileIO::ReadFile(contentRead, path, fileName);

	if (FileReadOutCode != FileIO::Ok)
		AVALON_CORE_ERROR("Could not read file");
	else
		AVALON_CORE_INFO("This is what's inside of {}{}: {}", path, fileName, contentRead);

	return new Sandbox();
}
