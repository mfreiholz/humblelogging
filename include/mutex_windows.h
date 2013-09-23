#ifndef HUMBLE_MUTEX_WINDOWS_HEADER
#define HUMBLE_MUTEX_WINDOWS_HEADER

#include <Windows.h>

namespace std {

class mutex
{
public:
  mutex();
  ~mutex();
  void lock();
  void unlock();

private:
  CRITICAL_SECTION _criticalSection;
};

template<typename TLockable>
class lock_guard
{
public:
  lock_guard(TLockable &lockable)
    : _lockable(lockable)
  {
    _lockable.lock();
  }
  
  ~lock_guard()
  {
    _lockable.unlock();
  }
  
private:
  TLockable _lockable;
};

}  // End of namespaces.
#endif
