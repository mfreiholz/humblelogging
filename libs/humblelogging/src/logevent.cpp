#include "humblelogging/logevent.h"
#include "humblelogging/util/processinfo.h"

HL_NAMESPACE_BEGIN

LogEvent::LogEvent(const std::string& loggerName, int level, const std::string& message, int line, const std::string& file, const std::string& func)
	: _loggerName(loggerName)
	, _level(level)
	, _message(message)
	, _line(line)
	, _file(file)
	, _function(func)
	, _time(time(NULL))
	, _pid(ProcessInfo::getProcessID())
	, _tid(ProcessInfo::getThreadID())
{
}

LogEvent::~LogEvent()
{
}

std::string LogEvent::fileName(const std::string& filePath)
{
	size_t pos2;
	if ((pos2 = filePath.find_last_of("/")) != std::string::npos || (pos2 = filePath.find_last_of("\\")) != std::string::npos)
	{
		return filePath.substr(pos2 + 1);
	}
	return filePath;
}

HL_NAMESPACE_END
