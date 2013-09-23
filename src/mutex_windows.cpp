#include "mutex_windows.h"

namespace std {

mutex::mutex()
{
  ::InitializeCriticalSection(&_criticalSection);
}

mutex::~mutex()
{
  ::DeleteCriticalSection(&_criticalSection);
}

void mutex::lock()
{
  ::EnterCriticalSection(&_criticalSection);
}

void mutex::unlock()
{
  ::LeaveCriticalSection(&_criticalSection);
}

}  // End of namespaces.
