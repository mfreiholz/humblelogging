#include "humblelogging/loglevel.h"

HL_NAMESPACE_BEGIN

std::string LogLevel::resolveLogLevel(int level)
{
	switch (level)
	{
		case LogLevel::Off:
			return std::string("off");

		case LogLevel::Fatal:
			return std::string("fatal");

		case LogLevel::Error:
			return std::string("error");

		case LogLevel::Warn:
			return std::string("warn");

		case LogLevel::Info:
			return std::string("info");

		case LogLevel::Debug:
			return std::string("debug");

		case LogLevel::Trace:
			return std::string("trace");

		case LogLevel::All:
			return std::string("all");

		default:
			return std::string("unknown");
	}
}

int LogLevel::resolveLogLevel(const std::string& level)
{
	if (level.compare(std::string("off")) == 0)
	{
		return LogLevel::Off;
	}
	else if (level.compare(std::string("fatal")) == 0)
	{
		return LogLevel::Fatal;
	}
	else if (level.compare(std::string("error")) == 0)
	{
		return LogLevel::Error;
	}
	else if (level.compare(std::string("warn")) == 0)
	{
		return LogLevel::Warn;
	}
	else if (level.compare(std::string("info")) == 0)
	{
		return LogLevel::Info;
	}
	else if (level.compare(std::string("debug")) == 0)
	{
		return LogLevel::Debug;
	}
	else if (level.compare(std::string("trace")) == 0)
	{
		return LogLevel::Trace;
	}
	else if (level.compare(std::string("all")) == 0)
	{
		return LogLevel::All;
	}
	return LogLevel::Off;
}

HL_NAMESPACE_END
