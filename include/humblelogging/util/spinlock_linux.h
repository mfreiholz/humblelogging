#ifndef HUMBLE_SPINLOCK_LINUX_HEADER
#define HUMBLE_SPINLOCK_LINUX_HEADER

#include <atomic>

#include "humblelogging/defines.h"

HL_NAMESPACE_BEGIN

class HUMBLE_EXPORT_API SpinLock
{
public:
  SpinLock();
  ~SpinLock();

  void lock();
  void unlock();

  bool tryLock();

private:
  std::atomic<bool> _val;
};

HL_NAMESPACE_END
#endif
