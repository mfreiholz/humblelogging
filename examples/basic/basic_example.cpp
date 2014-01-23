#include "humblelogging/api.h"

#ifdef __linux__
#include <sys/time.h>
#endif
#include <stdio.h>

HUMBLE_LOGGER(logger, "default");
HUMBLE_LOGGER(logger2, "default.2");
HUMBLE_LOGGER(logger3, "default.3");
HUMBLE_LOGGER(logger4, "default.4");

using namespace humble::logging;

#ifdef __linux__
long getTimestampMillis()
{
  struct timeval t;
  gettimeofday(&t, NULL);
  return (t.tv_sec * 1000 + t.tv_usec/1000) + 0.5;
}
#endif

#ifdef WIN32
long getTimestampMillis()
{
  static LARGE_INTEGER s_frequency;
  static BOOL s_use_qpc = QueryPerformanceFrequency(&s_frequency);
  if (s_use_qpc) {
    LARGE_INTEGER now;
    QueryPerformanceCounter(&now);
    return (1000LL * now.QuadPart) / s_frequency.QuadPart;
  } else {
    return GetTickCount();
  }
}
#endif

void logAllLevels()
{
  HL_TRACE(logger, "Trace log");
  HL_DEBUG(logger, "Debug log");
  HL_INFO (logger, "Info log");
  HL_WARN (logger, "Warn log");
  HL_ERROR(logger, "Error log");
  HL_FATAL(logger, "Fatal log");

  HL_TRACE(logger2, "Trace log");
  HL_DEBUG(logger2, "Debug log");
  HL_INFO (logger2, "Info log");
  HL_WARN (logger2, "Warn log");
  HL_ERROR(logger2, "Error log");
  HL_FATAL(logger2, "Fatal log");

  HL_TRACE(logger3, "Trace log");
  HL_DEBUG(logger3, "Debug log");
  HL_INFO (logger3, "Info log");
  HL_WARN (logger3, "Warn log");
  HL_ERROR(logger3, "Error log");
  HL_FATAL(logger3, "Fatal log");

  HL_TRACE(logger4, "Trace log");
  HL_DEBUG(logger4, "Debug log");
  HL_INFO (logger4, "Info log");
  HL_WARN (logger4, "Warn log");
  HL_ERROR(logger4, "Error log");
  HL_FATAL(logger4, "Fatal log");
}

int main(int argc, char **argv)
{
  // Initialize humble logging.
  Factory &fac = Factory::getInstance();
  
  // Change the default Formatter (optional).
  fac.setDefaultFormatter(new PatternFormatter("[%date] [%lls] [line=%line] [file=%filename] %m\n"));
  
  // Add Appender which doesn't log anywhere.
  fac.registerAppender(new NullAppender());

  // Add Appender which logs to STDOUT.
  ConsoleAppender *consoleAppender = new ConsoleAppender();
  fac.registerAppender(consoleAppender);

  // Add Appender which logs to file on disk.
  FileAppender *fileAppender = new FileAppender("humble.log", false);
  fac.registerAppender(fileAppender);

  // Add Appender which logs to file (rolling).
  RollingFileAppender *rfileAppender = new RollingFileAppender("humble-rolling.log", false, 5, 1024LL * 1024LL);
  fac.registerAppender(rfileAppender);
  
  fac.changeGlobalLogLevel(LogLevel::All);
  logAllLevels();
  fac.changeLogLevelRecursive("default", LogLevel::Warn);
  logAllLevels();

  // Bunch of logs for performance testing.
  //fac.changeGlobalLogLevel(LogLevel::All);
  //const long startMs = getTimestampMillis();
  //HL_TRACE(logger, "Begin of loop.");
  //for (int i = 0, max = 1000000; i < max; ++i) {
  //  HL_TRACE(logger, std::string("Blubb"));
  //}
  //HL_TRACE(logger, "End of loop.");
  //printf("Elapsed %ld ms\n", getTimestampMillis() - startMs);

  return 0;
}
