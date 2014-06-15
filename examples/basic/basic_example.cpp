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

  FileConfiguration conf("D:/Temp/logging.conf");
  int level = conf.getLogLevel(&logger);
  level = conf.getLogLevel(&fac.getLogger("core.network"));
  level = conf.getLogLevel(&fac.getLogger("core.network.logger"));
  level = conf.getLogLevel(&fac.getLogger("core.network.tcp"));
  level = conf.getLogLevel(&fac.getLogger("core.network.tcp.handler"));
  level = conf.getLogLevel(&fac.getLogger("Core"));
  level = conf.getLogLevel(&fac.getLogger("CoreNetwork"));
  level = conf.getLogLevel(&fac.getLogger("CoreNetworkTcp"));
  return 0;
}
