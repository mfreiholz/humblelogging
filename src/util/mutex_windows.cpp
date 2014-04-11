#include "humblelogging/util/mutex_windows.h"

namespace humble {
namespace logging {

Mutex::Mutex()
{
  ::InitializeCriticalSection(&_criticalSection);
}

Mutex::~Mutex()
{
  ::DeleteCriticalSection(&_criticalSection);
}

void Mutex::lock()
{
  ::EnterCriticalSection(&_criticalSection);
}

void Mutex::unlock()
{
  ::LeaveCriticalSection(&_criticalSection);
}

}}  // End of namespace.
