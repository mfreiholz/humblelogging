#include "humblelogging/util/processinfo.h"

#ifdef _WIN32
#include <Windows.h>
#else
#include <signal.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <unistd.h>
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

unsigned int ProcessInfo::getThreadID()
{
#ifdef _WIN32
	return GetCurrentThreadId();
#else
	return syscall(SYS_gettid); //return gettid();
#endif
}

HL_NAMESPACE_END
