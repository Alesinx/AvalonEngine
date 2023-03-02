#include <Avalon.h>

class Sandbox : public Avalon::Application
{
public:
	Sandbox() { }
	~Sandbox() { }
};

Avalon::Application* Avalon::CreateApplication()
{
	AVALON_LOG_INFO("Creating application...");

	//int n = 42;
	//AVALON_LOG_INFO("Example info log.");
	//AVALON_LOG_TRACE("Example trace log with a paramter: {}", n);
	//AVALON_LOG_WARNING("Example warning log with a parameter: {}", n);
	//AVALON_LOG_ERROR("Example error log with a parameter: {}", n);

	const std::string path = "C:/Dev/Avalon/";
	const std::string fileName = "Example.txt";
	const std::string contentToWrite = "Lorem ipsum dolor sit amet";
	std::string contentRead;

	AVALON_LOG_INFO("[File read/write test]");

	AVALON_LOG_INFO("Writing on file {}{}", path, fileName);
	const int FileWriteOutCode = FileIO::WriteFile(contentToWrite, path, fileName);
	const int FileReadOutCode = FileIO::ReadFile(contentRead, path, fileName);

	if (FileReadOutCode != FileIO::Ok)
		AVALON_LOG_ERROR("Could not read file");
	else
		AVALON_LOG_INFO("This is what's inside of {}{}: {}", path, fileName, contentRead);

	return new Sandbox();
}