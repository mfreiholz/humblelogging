#ifndef HUMBLE_MUTEX_HEADER
#define HUMBLE_MUTEX_HEADER

#ifdef WIN32
#include "mutex_windows.h"
#else
#include <mutex>
#endif

namespace humble {
namespace logging {

class MutexLockGuard
{
public:
  MutexLockGuard(Mutex &lockable)
    : _lockable(lockable)
  {
    _lockable.lock();
  }

  ~MutexLockGuard()
  {
    _lockable.unlock();
  }

private:
  Mutex &_lockable;
};

}}

#endif
