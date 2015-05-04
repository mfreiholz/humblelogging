#include "humblelogging/util/spinlock.h"

#include <Windows.h>

HL_NAMESPACE_BEGIN

class SpinLockPrivate
{
public:
  SpinLockPrivate() : val(0) {}
  LONG val;
};

SpinLock::SpinLock() :
  d(new SpinLockPrivate())
{
}

SpinLock::~SpinLock()
{
  unlock();
  delete d;
}

void SpinLock::lock()
{
  //DWORD sleepMs = 1;
  while (InterlockedExchange(&d->val, (LONG) 1) != 0) {
    // Try again, until somebody else changes the value to 0,
    // with a call to "unlock()".
    //Sleep(min(10, sleepMs++));
  }
}

void SpinLock::unlock()
{
  InterlockedExchange(&d->val, (LONG) 0);
}

bool SpinLock::tryLock()
{
  return InterlockedExchange(&d->val, (LONG) 1) == 0;
}

HL_NAMESPACE_END
