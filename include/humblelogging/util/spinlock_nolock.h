#ifndef HUMBLE_SPINLOCK_NOLOCK_HEADER
#define HUMBLE_SPINLOCK_NOLOCK_HEADER

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
};

HL_NAMESPACE_END
#endif
