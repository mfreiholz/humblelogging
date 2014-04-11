#ifndef HUMBLE_MUTEX_LINUX_HEADER
#define HUMBLE_MUTEX_LINUX_HEADER

#include <mutex>

#include "humblelogging/defines.h"

namespace humble {
namespace logging {

class HUMBLE_EXPORT_API Mutex
{
public:
  Mutex();
  ~Mutex();
  void lock();
  void unlock();

private:
  std::mutex _m;
};

}} // End of namespace.

#endif
