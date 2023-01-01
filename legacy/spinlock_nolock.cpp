#include "humblelogging/util/spinlock.h"

HL_NAMESPACE_BEGIN

class SpinLockPrivate
{
public:
};

SpinLock::SpinLock() :
  d(0)
{
}

SpinLock::~SpinLock()
{
  delete d;
}

void SpinLock::lock()
{
}

void SpinLock::unlock()
{
}

bool SpinLock::tryLock()
{
  return true;
}

HL_NAMESPACE_END
