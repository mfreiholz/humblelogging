#ifndef HUMBLE_PROCESSINFO_HEADER
#define HUMBLE_PROCESSINFO_HEADER

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include <signal.h>
#endif

#include "humblelogging/defines.h"

namespace humble {
namespace logging {

class ProcessInfo
{
public:
  static unsigned int getProcessID()
  {
#ifdef _WIN32
    return GetCurrentProcessId();
#else
    return getpid();
#endif
  }

  static unsigned int getThreadID()
  {
#ifdef _WIN32
    return GetCurrentThreadId();
#else
    return syscall(SYS_gettid);
    //return gettid();
#endif
  }
};

}} // End of namespace.
#endif
