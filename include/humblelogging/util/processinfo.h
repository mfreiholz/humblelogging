#ifndef HUMBLE_PROCESSINFO_HEADER
#define HUMBLE_MUTEX_WINDOWS_HEADER

#ifdef _WIN32
#include <Windows.h>
#else
#include <sys/types.h>
#include <unistd.h>
#endif // _WIN32



#include "humblelogging/defines.h"

namespace humble
{
namespace logging
{

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
    return gettid();
#endif
  }
};

}
} // End of namespace.
#endif
