#include "humblelogging/formatter/simpleformatter.h"
#include "humblelogging/logevent.h"
#include "humblelogging/loglevel.h"
#include <cstdio>
#include <sstream>

HL_NAMESPACE_BEGIN

SimpleFormatter::SimpleFormatter()
{}

SimpleFormatter::SimpleFormatter(const SimpleFormatter&)
{}

std::unique_ptr<Formatter> SimpleFormatter::clone() const
{
	return std::make_unique<SimpleFormatter>(*this);
}

std::string SimpleFormatter::format(const LogEvent& logEvent) const
{
	std::string logLevelString = LogLevel::resolveLogLevel(logEvent.getLogLevel());

	struct tm* timeinfo = localtime(&logEvent.getTime());
	char timeString[80];
	strftime(timeString, 80, "%Y-%m-%d %H:%M:%S", timeinfo);

	std::stringstream ss;
	ss
		<< "[" << timeString << "]"
		<< "[" << logEvent.getLoggerName() << "]"
		<< "[" << logLevelString << "]"
		<< "[pid=" << logEvent.getPid() << "]"
		<< "[tid=" << logEvent.getTid() << "]"
		<< "[file=" << LogEvent::fileName(logEvent.getFile()) << "]"
		<< "[line=" << logEvent.getLine() << "]"
		<< "[func=" << logEvent.getFunction() << "]"
		<< " "
		<< logEvent.getMessage()
		<< "\n";
	return ss.str(); // optional: std::move(ss.str())
}

HL_NAMESPACE_END
