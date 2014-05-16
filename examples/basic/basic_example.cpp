#include "humblelogging/api.h"

// 1# Create new logger.
HUMBLE_LOGGER(logger, "default");

using namespace humble::logging;

int main(int argc, char **argv)
{
  // 2# Initialize some default settings.
  // Change the default LogLevel, which every NEW Logger will have.
  Factory &fac = Factory::getInstance();
  fac.setDefaultLogLevel(LogLevel::All);

  // 3# Add Appender which logs to STDOUT.
  fac.registerAppender(new ConsoleAppender());

  // 4# Do some logging.
  HL_TRACE(logger, "Trace log");
  HL_DEBUG(logger, "Debug log");
  HL_INFO (logger, "Info log");
  HL_WARN (logger, "Warn log");
  HL_ERROR(logger, "Error log");
  HL_FATAL(logger, "Fatal log");

  return 0;
}
