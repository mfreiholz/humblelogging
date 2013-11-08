#include "humble-logging.h"

#include <sys/time.h>
#include <stdio.h>

HUMBLE_LOGGER(logger, "default");

using namespace humble::logging;

int main(int argc, char **argv)
{
  struct timeval start, end;
  gettimeofday(&start, NULL);

  HL_DEBUG(logger, "Initialize logging (this text should NOT be logged).");

  Factory &fac = Factory::getInstance();
  //fac.registerAppender(new NullAppender());
  fac.registerAppender(new ConsoleAppender());
  //fac.registerAppender(new FileAppender("humble.log"));
  fac.changeGlobalLogLevel(LogLevel::All);
  
  HL_TRACE(logger, "Trace log");
  HL_DEBUG(logger, "Debug log");
  HL_INFO (logger, "Info log");
  HL_WARN (logger, "Warn log");
  HL_ERROR(logger, "Error log");
  HL_FATAL(logger, "Fatal log");

  HL_TRACE(logger, "Begin of loop.");
  for (int i = 0, max = 1000000; i < max; ++i) {
    HL_TRACE(logger, std::string("Blubb"));
  }
  HL_TRACE(logger, "End of loop.");
  
  gettimeofday(&end, NULL);
  long seconds  = end.tv_sec  - start.tv_sec;
  long useconds = end.tv_usec - start.tv_usec;
  long mtime = ((seconds) * 1000 + useconds/1000.0) + 0.5;
  printf("Elapsed %ld ms\n", mtime);
  return 0;
}
