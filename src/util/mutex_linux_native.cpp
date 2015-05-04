#include "humblelogging/util/mutex.h"

#include <pthread.h>

HL_NAMESPACE_BEGIN

class MutexPrivate
{
public:
  pthread_mutex_t m;
};

Mutex::Mutex() :
  d(new MutexPrivate())
{
  pthread_mutex_init(&d->m, NULL);
}

Mutex::~Mutex()
{
  unlock();
  delete d;
}

void Mutex::lock()
{
  pthread_mutex_lock(&d->m);
}

void Mutex::unlock()
{
  pthread_mutex_unlock(&d->m);
}

HL_NAMESPACE_END
