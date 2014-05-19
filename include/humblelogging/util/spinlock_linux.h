#ifndef HUMBLE_SPINLOCK_LINUX_HEADER
#define HUMBLE_SPINLOCK_LINUX_HEADER

#include <atomic>

namespace humble {
namespace logging {

class SpinLock
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
