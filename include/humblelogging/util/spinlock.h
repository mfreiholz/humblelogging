#ifndef HUMBLE_SPINLOCK_HEADER
#define HUMBLE_SPINLOCK_HEADER

#include "humblelogging/defines.h"

HL_NAMESPACE_BEGIN

class SpinLockPrivate;
class HUMBLE_EXPORT_API SpinLock
{
  friend class SpinLockPrivate;
  SpinLockPrivate *d;

public:
  SpinLock();
  ~SpinLock();
  void lock();
  void unlock();
  bool tryLock();
};

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
