#include "humblelogging/util/spinlock_linux.h"

#include <thread>
#include <chrono>

HL_NAMESPACE_BEGIN

SpinLock::SpinLock()
{
}

SpinLock::~SpinLock()
{
  unlock();
}

void SpinLock::lock()
{
  //int sleepMs = 1;
  while (_val.exchange(true) == true) {
    // Try again, until somebody else changes the value to 0,
    // with a call to "unlock()".
    //std::this_thread::sleep_for(std::chrono::milliseconds(std::min(10, sleepMs++)));
  }
}

void SpinLock::unlock()
{
  _val.exchange(false);
}

bool SpinLock::tryLock()
{
  return _val.exchange(true) == false;
}

HL_NAMESPACE_END
