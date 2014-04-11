#include "humblelogging/util/mutex_linux.h"

namespace humble {
namespace logging {

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

}}  // End of namespace.
