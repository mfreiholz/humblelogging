#include "humblelogging/util/mutex.h"

HL_NAMESPACE_BEGIN

class MutexPrivate
{};

Mutex::Mutex() :
  d(0)
{
}

Mutex::~Mutex()
{
  delete d;
}

void Mutex::lock()
{
}

void Mutex::unlock()
{
}

HL_NAMESPACE_END
