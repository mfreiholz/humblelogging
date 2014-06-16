#ifndef SPINLOCK_WINDOWS_HEADER
#define SPINLOCK_WINDOWS_HEADER

#include <Windows.h>

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
  LONG _val;
};

}}

#endif
