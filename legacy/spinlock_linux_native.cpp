#include "humblelogging/util/spinlock.h"

HL_NAMESPACE_BEGIN

class SpinLockPrivate
{
public:
  SpinLockPrivate() : val(0) {}
  int val;
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
  while (__sync_lock_test_and_set(&d->val, 1) != 0) {
    continue;
  }
}

void SpinLock::unlock()
{
  __sync_lock_test_and_set(&d->val, 0);
}

bool SpinLock::tryLock()
{
  return __sync_lock_test_and_set(&d->val, 1) == 0;
}

HL_NAMESPACE_END
