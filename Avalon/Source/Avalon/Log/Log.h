#pragma once

#include <string>

#define AVALON_CORE_INFO(str, ...) Avalon::Logging::Log(Avalon::Logging::LogLevel::Info, "", std::format(str, ##__VA_ARGS__))
#define AVALON_CORE_TRACE(str, ...) Avalon::Logging::Log(Avalon::Logging::LogLevel::Trace, __FUNCTION__, std::format(str, ##__VA_ARGS__))
#define AVALON_CORE_WARNING(str, ...) Avalon::Logging::Log(Avalon::Logging::LogLevel::Warning, __FUNCTION__, std::format(str, ##__VA_ARGS__))
#define AVALON_CORE_ERROR(str, ...) Avalon::Logging::Log(Avalon::Logging::LogLevel::Error, __FUNCTION__,  std::format(str, ##__VA_ARGS__))

#define AVALON_INFO(str, ...) Avalon::Logging::Log(Avalon::Logging::LogLevel::Info, "", std::format(str, ##__VA_ARGS__))
#define AVALON_TRACE(str, ...) Avalon::Logging::Log(Avalon::Logging::LogLevel::Trace, __FUNCTION__, std::format(str, ##__VA_ARGS__))
#define AVALON_WARNING(str, ...) Avalon::Logging::Log(Avalon::Logging::LogLevel::Warning, __FUNCTION__, std::format(str, ##__VA_ARGS__))
#define AVALON_ERROR(str, ...) Avalon::Logging::Log(Avalon::Logging::LogLevel::Error, __FUNCTION__,  std::format(str, ##__VA_ARGS__))

namespace Avalon::Logging
{
	enum Color
	{
		Red = 31,
		Green,
		Yellow,
		Blue,
		Magenta,
		Cyan,
		White
	};

	enum class LogLevel
	{
		Info = 0,
		Trace,
		Warning,
		Error
	};

	void Log(LogLevel LogLevel, const std::string& location, const std::string& message);
}