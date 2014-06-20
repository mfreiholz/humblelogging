#include "humblelogging/api.h"
#include "humblelogging/util/mutex.h"

#ifdef __linux__
#include <sys/time.h>
#include <pthread.h>
#endif

#include <stdio.h>
#include <vector>
#include <cstring>

HUMBLE_LOGGER(logger, "default");

using namespace humble::logging;

struct ExampleData {
  int threadCount;
  unsigned long threadIterations;

  ExampleData()
  {
    threadCount = 1;
    threadIterations = 1000000LL;
  }
} OPTS;

#ifdef __linux__
long getTimestampMillis()
{
  struct timeval t;
  gettimeofday(&t, NULL);
  return (t.tv_sec * 1000 + t.tv_usec/1000) + 0.5;
}

void* threadWork1(void *args)
{
  for (unsigned long i = 0; i < OPTS.threadIterations; ++i) {
    HL_TRACE(logger, std::string("A apple doesn't taste like a banana. Surprise!"));
  }
  return NULL;
}
#endif

#ifdef _WIN32
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

DWORD WINAPI threadWork1(LPVOID lpThreadParameter)
{
  for (unsigned long i = 0; i < OPTS.threadIterations; ++i) {
    HL_TRACE(logger, std::string("A apple doesn't taste like a banana. Surprise!"));
  }
  return 0;
}
#endif

/*
  Parameters:
  *.exe [threadCount] [eventsPerThread] [appender]

  Defaults:
  threadCount = 1
  eventsPerThread = 1000000
  appender = none

  Possible values for "appender":
  none, null, console, file, rfile
*/
int main(int argc, char **argv)
{
  Factory &fac = Factory::getInstance();
  fac.setDefaultLogLevel(LogLevel::All);

  if (argc > 1) {
    int threadCount = atoi(argv[1]);
    if (threadCount > 0)
      OPTS.threadCount = threadCount;
  }
  if (argc > 2) {
    unsigned long num = atol(argv[2]);
    if (num > 0)
      OPTS.threadIterations = num;
  }
  if (argc > 3) {
    const char *appender = argv[3];
    if (strcmp(appender, "null") == 0)
      fac.registerAppender(new NullAppender());
    else if (strcmp(appender, "console") == 0)
      fac.registerAppender(new ConsoleAppender());
    else if (strcmp(appender, "file") == 0)
      fac.registerAppender(new FileAppender("humble.log", false));
    else if (strcmp(appender, "rfile") == 0)
      fac.registerAppender(new RollingFileAppender("humble-rolling.log", false, 5, 1024LL * 1024LL));
  }

  printf("\n");
  printf("Setup\n");
  printf("  Threads: %d\n", OPTS.threadCount);
  printf("  Events per thread: %ld\n", OPTS.threadIterations);
  printf("\n");
  printf("... running - please wait ...\n");

  const long startMs = getTimestampMillis();

#ifdef _WIN32
  // Start logging threads.
  std::vector<HANDLE> threads(OPTS.threadCount);
  for (int i = 0; i < OPTS.threadCount; ++i) {
    HANDLE t = CreateThread(NULL, 0, threadWork1, NULL, 0, NULL);
    threads.push_back(t);
  }
  // Wait until they are done.
  for (int i = 0; i < threads.size(); ++i) {
    WaitForSingleObject(threads[i], INFINITE);
  }
#endif

#ifdef __linux__
  // Start logging threads.
  std::vector<pthread_t> threads(OPTS.threadCount);
  for (int i = 0; i < OPTS.threadCount; ++i) {
    pthread_t t;
    pthread_create(&t, NULL, &threadWork1, NULL);
    threads.push_back(t);
  }
  // Wait until they are done.
  for (int i = 0; i < threads.size(); ++i) {
    pthread_join(threads[i], NULL);
  }
#endif

  const long endMs = getTimestampMillis();
  const long durationMs = endMs - startMs;
  const unsigned long logEventsCount = OPTS.threadIterations * (unsigned long) OPTS.threadCount;
  double throughputPerSecond = (double) logEventsCount / (double) durationMs;
  throughputPerSecond = throughputPerSecond * (double) 1000;
  
  printf("\n");
  printf("Done.\n");
  printf("  Events: %ld\n", logEventsCount);
  printf("  Duration: %ld ms / %f s\n", durationMs, (double) durationMs / (double) 1000);
  printf("  Throughput: %f events/second\n", throughputPerSecond);
  printf("\n");

  return 0;
}
