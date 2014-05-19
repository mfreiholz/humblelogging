#include "humblelogging/util/spinlock_windows.h"

namespace humble {
namespace logging {

SpinLock::SpinLock()
{
}

SpinLock::~SpinLock()
{
  unlock();
}

void SpinLock::lock()
{
  DWORD sleepMs = 1;
  while (InterlockedExchange(&_val, (LONG) 1) == 1) {
    // Try again, until somebody else changes the value to 0,
    // with a call to "unlock()".
    Sleep(min(10, sleepMs++));
  }
}

void SpinLock::unlock()
{
  InterlockedExchange(&_val, (LONG) 0);
}

bool SpinLock::tryLock()
{
  return InterlockedExchange(&_val, (LONG) 1) == 0;
}

}} // End of namespace.
