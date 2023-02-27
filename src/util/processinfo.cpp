#include "humblelogging/util/processinfo.h"

#ifdef _WIN32
#include <Windows.h>
#else
#include <signal.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>
#endif

HL_NAMESPACE_BEGIN

unsigned int ProcessInfo::getProcessID()
{
#ifdef _WIN32
	return GetCurrentProcessId();
#else
	return getpid();
#endif
}

size_t ProcessInfo::getThreadID()
{
#ifdef _WIN32
	return GetCurrentThreadId();
#elif defined(__APPLE__) && defined(__MACH__)
    uint64_t tid64;
    pthread_threadid_np(nullptr, &tid64);
    return static_cast<size_t>(tid64);
#else
	return syscall(SYS_gettid); //return gettid();
#endif
}

HL_NAMESPACE_END
