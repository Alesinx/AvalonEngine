#include "AvalonPch.h"
#include "Log.h"

void Avalon::Logging::Log(LogLevel LogLevel, const std::string& location, const std::string& message)
{
	int colorCode = Color::White;
	std::string prefix = "";
	std::string str = message;

	switch(LogLevel)
	{
	case LogLevel::Trace:
		prefix = std::format("[Trace in {}]: ", location);
		break;
	case LogLevel::Warning:
		colorCode = Color::Yellow;
		prefix = std::format("[Warning in {}]: ", location);
		break;
	case LogLevel::Error:
		colorCode = Color::Red;
		prefix = std::format("[Error in {}]: ", location);
		break;
	}

	std::cout << std::format("\033[{}m{}{}", colorCode, prefix, str) << "\n";
}