#pragma once

#include <string>

namespace Avalon::FileIO
{
	enum Code
	{
		CouldNotRead = -1,
		Ok = 0
	};

	int ReadFile(std::string& outContent, std::string path, std::string fileName);

	int WriteFile(const std::string& inContent, std::string path, std::string fileName);
}