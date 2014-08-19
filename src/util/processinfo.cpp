#include "humblelogging/util/processinfo.h"

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include <signal.h>
#endif

namespace humble {
namespace logging {

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
  return syscall(SYS_gettid);  //return gettid();
#endif
}

}} // End of namespace.
