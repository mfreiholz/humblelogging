#include "humblelogging/util/mutex_linux.h"

HL_NAMESPACE_BEGIN

Mutex::Mutex()
{
}

Mutex::~Mutex()
{
  _m.unlock();
}

void Mutex::lock()
{
  _m.lock();
}

void Mutex::unlock()
{
  _m.unlock();
}

HL_NAMESPACE_END
