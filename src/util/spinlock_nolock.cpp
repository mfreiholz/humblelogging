#include "humblelogging/util/spinlock_nolock.h"

HL_NAMESPACE_BEGIN

SpinLock::SpinLock()
{
}

SpinLock::~SpinLock()
{
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
