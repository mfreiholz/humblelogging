#ifndef SPINLOCK_WINDOWS_HEADER
#define SPINLOCK_WINDOWS_HEADER

#include <Windows.h>

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
  LONG _val;
};

}}

#endif
