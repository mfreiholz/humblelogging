#include "humblelogging/util/mutex_windows.h"

HL_NAMESPACE_BEGIN

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

HL_NAMESPACE_END
