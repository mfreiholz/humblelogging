#include "humble-logging.h"

HUMBLE_LOGGER(logger, "default");

using namespace humble::logging;

int main(int argc, char **argv)
{
  HL_DEBUG(logger, "Initialize logging (this text should NOT be logged).");

  Factory &fac = Factory::getInstance();
  fac.registerAppender(new ConsoleAppender());
  fac.registerAppender(new FileAppender("humble.log"));
  fac.changeGlobalLogLevel(LogLevel::All);
  
  HL_TRACE(logger, "Trace log");
  HL_DEBUG(logger, "Debug log");
  HL_INFO (logger, "Info log");
  HL_WARN (logger, "Warn log");
  HL_ERROR(logger, "Error log");
  HL_FATAL(logger, "Fatal log");

  HL_TRACE(logger, "Begin of loop.");
  for (int i = 0; i < 10; ++i) {
    HL_TRACE(logger, std::string("Iteration ") + std::string(" of 10"));
  }
  HL_TRACE(logger, "End of loop.");
  return 0;
}
