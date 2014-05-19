#ifndef HUMBLE_SPINLOCK_HEADER
#define HUMBLE_SPINLOCK_HEADER

#ifdef _WIN32
#include "spinlock_windows.h"
#else
#include "spinlock_linux.h"
#endif

namespace humble {
namespace logging {

class SpinLocker
{
public:
  SpinLocker(SpinLock &l)
    : _lockable(l)
  {
    _lockable.lock();
  }

  ~SpinLocker()
  {
    _lockable.unlock();
  }

private:
  SpinLock &_lockable;
};

}}

#endif
