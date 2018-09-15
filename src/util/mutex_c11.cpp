#include "humblelogging/util/mutex.h"
#include <mutex>

HL_NAMESPACE_BEGIN

class MutexPrivate
{
public:
	std::mutex m;
};

Mutex::Mutex()
	: d(new MutexPrivate())
{
}

Mutex::~Mutex()
{
	delete d;
}

void Mutex::lock()
{
	d->m.lock();
}

void Mutex::unlock()
{
	d->m.unlock();
}

HL_NAMESPACE_END
