#include "humblelogging/util/mutex.h"

#include <Windows.h>

HL_NAMESPACE_BEGIN

class MutexPrivate
{
public:
  CRITICAL_SECTION criticalSection;
};

Mutex::Mutex() :
  d(new MutexPrivate())
{
  ::InitializeCriticalSection(&d->criticalSection);
}

Mutex::~Mutex()
{
  ::DeleteCriticalSection(&d->criticalSection);
  delete d;
}

void Mutex::lock()
{
  ::EnterCriticalSection(&d->criticalSection);
}

void Mutex::unlock()
{
  ::LeaveCriticalSection(&d->criticalSection);
}

HL_NAMESPACE_END
