#include "humblelogging/util/spinlock_nolock.h"

namespace humble {
namespace logging {

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

}} // End of namespace.
