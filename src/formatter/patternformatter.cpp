#include "humblelogging/formatter/patternformatter.h"

#include <cstdio>
#include <sstream>

#include "humblelogging/logevent.h"
#include "humblelogging/loglevel.h"

HL_NAMESPACE_BEGIN

///////////////////////////////////////////////////////////////////////////////
// PatternFormatter
///////////////////////////////////////////////////////////////////////////////

PatternFormatter::PatternFormatter(const std::string& pattern)
	: _pattern(pattern)
{
}

PatternFormatter::PatternFormatter(const PatternFormatter& other)
{
	_pattern = other._pattern;
}

PatternFormatter::~PatternFormatter()
{
}

Formatter* PatternFormatter::copy() const
{
	return new PatternFormatter(*this);
}

std::string PatternFormatter::format(const LogEvent& logEvent) const
{
	std::string s = _pattern;
	size_t pos = std::string::npos;
	if ((pos = s.find("%name")) != std::string::npos)
	{
		s.replace(pos, 5, logEvent.getLoggerName());
	}
	if ((pos = s.find("%lls")) != std::string::npos)
	{
		const std::string lls = LogLevel::resolveLogLevel(logEvent.getLogLevel());
		s.replace(pos, 4, lls);
	}
	if ((pos = s.find("%m")) != std::string::npos)
	{
		s.replace(pos, 2, logEvent.getMessage());
	}
	if ((pos = s.find("%line")) != std::string::npos)
	{
		char buff[10];
		sprintf(buff, "%d", logEvent.getLine());
		s.replace(pos, 5, buff);
	}
	if ((pos = s.find("%pid")) != std::string::npos)
	{
		char buff[10];
		sprintf(buff, "%d", logEvent.getPid());
		s.replace(pos, 4, buff);
	}
	if ((pos = s.find("%tid")) != std::string::npos)
	{
		char buff[10];
		sprintf(buff, "%d", logEvent.getTid());
		s.replace(pos, 4, buff);
	}
	if ((pos = s.find("%filename")) != std::string::npos)
	{
		std::string tmp = logEvent.getFile();
		size_t pos2;
		if ((pos2 = tmp.find_last_of("/")) != std::string::npos || (pos2 = tmp.find_last_of("\\")) != std::string::npos)
		{
			s.replace(pos, 9, tmp.substr(pos2 + 1));
		}
		else
		{
			s.replace(pos, 9, logEvent.getFile());
		}
	}
	if ((pos = s.find("%file")) != std::string::npos)
	{
		s.replace(pos, 5, logEvent.getFile());
	}
	if ((pos = s.find("%func")) != std::string::npos)
	{
		s.replace(pos, 5, logEvent.getFunction());
	}
	if ((pos = s.find("%date")) != std::string::npos)
	{
		struct tm* timeinfo = localtime(&logEvent.getTime());
		char timeString[80];
		strftime(timeString, 80, "%Y-%m-%d %H:%M:%S", timeinfo);
		s.replace(pos, 5, timeString);
	}
	return s; // optional: std::move(s)
}

HL_NAMESPACE_END