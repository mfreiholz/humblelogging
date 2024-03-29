#include "humblelogging/humblelogging.h"
#include <chrono>
#include <condition_variable>
#include <cstdlib>
#include <cstring>
#include <functional>
#include <future>
#include <stdio.h>
#include <thread>
#include <vector>

using namespace humble::logging;
HUMBLE_LOGGER(logger, "default");

int THREAD_COUNT = 1;
uint64_t EVENTS_PER_THREAD = 20000000ull;
bool FORMATTED_MESSAGES = false;

/*
  Parameters:
  *.exe [threadCount] [eventsPerThread] [appender] [formatted:bool(0,1)]

  Defaults:
	threadCount = 1
	eventsPerThread = 1000000
	appender = none
	formatted = 0

  Possible values for "appender":
  none, null, console, file, rfile
*/
int main(int argc, char** argv)
{
	Factory& fac = Factory::getInstance();

	if (argc > 1)
	{
		int threadCount = atoi(argv[1]);
		if (threadCount > 0)
			THREAD_COUNT = threadCount;
	}
	if (argc > 2)
	{
		unsigned long num = atol(argv[2]);
		if (num > 0)
			EVENTS_PER_THREAD = num;
	}
	if (argc > 3)
	{
		const char* appender = argv[3];
		if (strcmp(appender, "null") == 0)
			fac.registerAppender(std::make_shared<NullAppender>());
		else if (strcmp(appender, "console") == 0)
			fac.registerAppender(std::make_shared<ConsoleAppender>());
		else if (strcmp(appender, "file") == 0)
			fac.registerAppender(std::make_shared<FileAppender>("humble.log", false));
		else if (strcmp(appender, "rfile") == 0)
			fac.registerAppender(std::make_shared<RollingFileAppender>("humble-rolling.log", false, 5, 1024L * 1024L));
	}
	if (argc > 4)
	{
		const auto yesno = std::stoi(argv[4]);
		FORMATTED_MESSAGES = yesno != 0;
	}

	printf("\n");
	printf("Setup\n");
	printf("  Threads: %d\n", THREAD_COUNT);
	printf("  Events per thread: %" PRIu64 "\n", EVENTS_PER_THREAD);
	printf("  Formatted messages: %s\n", FORMATTED_MESSAGES ? "Yes" : "No");
	printf("\n");
	printf("... running - please wait ...\n");

	std::function<void()> threadWorkFunc;
	std::atomic<uint64_t> cnt = 0;
	if (FORMATTED_MESSAGES)
	{
		threadWorkFunc = [&cnt]() {
			for (uint64_t logCount = 0; logCount < EVENTS_PER_THREAD; ++logCount)
			{
				HL_TRACE_F(logger, "A %s doesn't taste like a %s. Surprise!", "apple", "banana");
				cnt++;
			}
		};
	}
	else
	{
		threadWorkFunc = [&cnt]() {
			for (uint64_t logCount = 0; logCount < EVENTS_PER_THREAD; ++logCount)
			{
				HL_TRACE(logger, "A apple doesn't taste like a banana. Surprise!");
				cnt++;
			}
		};
	}

	// Startup workers.
	// Do not immediately start it's work, we have to wait until all workers are started.
	std::vector<std::future<void>> workers;
	std::condition_variable startCondition;
	std::mutex startConditionMutex;
	for (auto i = 0; i < THREAD_COUNT; ++i)
	{
		auto f = std::async([&]() -> void {
			std::unique_lock l(startConditionMutex);
			startCondition.wait(l);
			l.unlock();
			threadWorkFunc();
		});
		workers.push_back(std::move(f));
	}
	std::this_thread::sleep_for(std::chrono::seconds(1));

	// Run !!!
	const auto startedAt = std::chrono::steady_clock::now();
	startCondition.notify_all();
	workers.clear(); // Waits for all futures, because std::future destructor waits.
	const auto endedAt = std::chrono::steady_clock::now();

	// Prepare result.
	const auto duration = endedAt - startedAt;
	const uint64_t logEventsCount = EVENTS_PER_THREAD * (unsigned long)THREAD_COUNT;
	const auto logsPerSecond = (double)logEventsCount / static_cast<double>(std::chrono::duration_cast<std::chrono::seconds>(duration).count());

	printf("\n");
	printf("Done.\n");
	printf("  Events: %" PRIu64 " (cnt=%" PRIu64 ")\n", logEventsCount, cnt.load());
	printf("  Duration: %" PRId64 " ms / %" PRId64 " s\n", std::chrono::duration_cast<std::chrono::milliseconds>(duration).count(), std::chrono::duration_cast<std::chrono::seconds>(duration).count());
	printf("  Throughput: %.2f events/second\n", logsPerSecond);
	printf("\n");

	return 0;
}