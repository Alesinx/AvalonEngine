#include "FileIO.h"
#include "Avalon/Log/Log.h"

#include <fstream>
#include <sstream>

namespace Avalon::FileIO
{
	int ReadFile(std::string& outContent, std::string path, std::string fileName)
	{
		std::ifstream iStream(path + fileName);
		std::stringstream buffer;

		if (!iStream.is_open())
			return Code::CouldNotRead;

		buffer << iStream.rdbuf(); // Load the whole file into a string buffer
		outContent = buffer.str(); // Copy buffer content

		iStream.close();
		
		return Code::Ok;
	}

	int WriteFile(const std::string& inContent, std::string path, std::string fileName)
	{
		std::ofstream oStream;
		oStream.open(path + fileName);
		oStream << inContent;
		oStream.close();
		return 0;
	}
};