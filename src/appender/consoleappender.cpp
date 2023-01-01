#include "humblelogging/appender/consoleappender.h"
#include "humblelogging/formatter.h"
#include <iostream>

HL_NAMESPACE_BEGIN

void ConsoleAppender::log(const LogEvent& logEvent)
{
	std::lock_guard lock(_mutex);
	if (!_formatter)
	{
		return;
	}
	std::cout << _formatter->format(logEvent);
}

HL_NAMESPACE_END
