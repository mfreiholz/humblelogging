#ifndef HUMBLE_SPINLOCK_HEADER
#define HUMBLE_SPINLOCK_HEADER

#include "humblelogging/defines.h"

#ifdef _WIN32
#include "spinlock_windows.h"
#else
#include "spinlock_linux.h"
#endif

HL_NAMESPACE_BEGIN

class HUMBLE_EXPORT_API SpinLocker
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

HL_NAMESPACE_END
#endif
