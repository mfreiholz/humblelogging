#ifndef HUMBLE_SPINLOCK_LINUX_HEADER
#define HUMBLE_SPINLOCK_LINUX_HEADER

#include <atomic>

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

private:
  std::atomic<bool> _val;
};

}}

#endif
