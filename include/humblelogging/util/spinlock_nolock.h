#ifndef HUMBLE_SPINLOCK_NOLOCK_HEADER
#define HUMBLE_SPINLOCK_NOLOCK_HEADER

#include "humblelogging/defines.h"

namespace humble {
namespace logging {

class HUMBLE_EXPORT_API SpinLock
{
public:
  SpinLock();
  ~SpinLock();
  void lock();
  void unlock();
  bool tryLock();
};

}}

#endif