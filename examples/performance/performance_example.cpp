#include "humblelogging/api.h"

#ifdef __linux__
#include <sys/time.h>
#endif
#include <stdio.h>

HUMBLE_LOGGER(logger, "default");

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

int main(int argc, char **argv)
{
  // Initialize default settings.
  Factory &fac = Factory::getInstance();
  fac.setDefaultLogLevel(LogLevel::All);
  fac.setDefaultFormatter(new PatternFormatter("[%date] [%lls] [line=%line] [file=%filename] %m\n"));

  // Do X logs with a specific appender.
  // Comment in/out the appender to be meassured.
  
//  fac.registerAppender(new NullAppender());

//  ConsoleAppender *consoleAppender = new ConsoleAppender();
//  fac.registerAppender(consoleAppender);

  FileAppender *fileAppender = new FileAppender("humble.log", false);
  fac.registerAppender(fileAppender);

//  RollingFileAppender *rfileAppender = new RollingFileAppender("humble-rolling.log", false, 5, 1024LL * 1024LL);
//  fac.registerAppender(rfileAppender);

  // Bunch of logs for performance testing.
  const int max = 1000000;
  const long startMs = getTimestampMillis();
  HL_TRACE(logger, "Begin of loop.");
  for (int i = 0; i < max; ++i) {
    HL_TRACE(logger, std::string("A apple doesn't taste like a banana. Surprise!"));
  }
  HL_TRACE(logger, "End of loop.");
  printf("Logged %d events in %ld ms\n", max, getTimestampMillis() - startMs);

  return 0;
}
