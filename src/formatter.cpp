#include "formatter.h"

#include <sstream>

#include "loglevel.h"

namespace humble {
namespace logging {

///////////////////////////////////////////////////////////////////////////////
// Formatter
///////////////////////////////////////////////////////////////////////////////

Formatter::Formatter()
{
}

Formatter::~Formatter()
{
}

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
    << "[" << timeString << "] "
    << "[" << logLevelString << "] "
    << "[line=" << logEvent.getLine() << "] "
    << "[file=" << logEvent.getFile() << "] "
    << logEvent.getMessage()
    << "\n";
  return ss.str();
}

}}  // End of namespaces.
