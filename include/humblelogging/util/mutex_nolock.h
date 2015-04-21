#ifndef HUMBLE_MUTEX_NOLOCK_HEADER
#define HUMBLE_MUTEX_NOLOCK_HEADER

#include "humblelogging/defines.h"

HL_NAMESPACE_BEGIN

class HUMBLE_EXPORT_API Mutex
{
public:
  Mutex();
  ~Mutex();
  void lock();
  void unlock();
};

HL_NAMESPACE_END
#endif
