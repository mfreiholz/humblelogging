#ifndef HUMBLE_MUTEX_NOLOCK_HEADER
#define HUMBLE_MUTEX_NOLOCK_HEADER

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
};

}}
#endif
