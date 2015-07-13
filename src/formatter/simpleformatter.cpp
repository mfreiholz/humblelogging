#include "humblelogging/formatter/simpleformatter.h"

#include <sstream>
#include <cstdio>

#include "humblelogging/loglevel.h"
#include "humblelogging/logevent.h"

HL_NAMESPACE_BEGIN

///////////////////////////////////////////////////////////////////////////////
// SimpleFormatter
///////////////////////////////////////////////////////////////////////////////

SimpleFormatter::SimpleFormatter()
{
}

SimpleFormatter::~SimpleFormatter()
{
}

Formatter* SimpleFormatter::copy() const
{
  return new SimpleFormatter(*this);
}

std::string SimpleFormatter::format(const LogEvent &logEvent) const
{
  std::string logLevelString = LogLevel::resolveLogLevel(logEvent.getLogLevel());

  struct tm *timeinfo = localtime(&logEvent.getTime());
  char timeString [80];
  strftime(timeString, 80, "%Y-%m-%d %H:%M:%S", timeinfo);

  std::stringstream ss;
  ss
    << "[" << timeString << "]"
    << "[" << logLevelString << "]"
    << "[pid=" << logEvent.getPid() << "]"
    << "[tid=" << logEvent.getTid() << "]"
    << "[file=" << logEvent.getFile() << "]"
    << "[line=" << logEvent.getLine() << "]"
#ifdef HUMBLE_INCLUDE_PRETTY_FUNCTION
    << "[func=" << logEvent.getFunction() << "]"
#endif
    << " "
    << logEvent.getMessage()
    << "\n";
  return ss.str(); // optional: std::move(ss.str())
}

HL_NAMESPACE_END