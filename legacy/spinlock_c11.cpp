#include "humblelogging/util/spinlock.h"

#include <atomic>
//#include <thread>
//#include <chrono>

HL_NAMESPACE_BEGIN

class SpinLockPrivate
{
public:
	std::atomic<bool> val;
};

SpinLock::SpinLock()
	: d(new SpinLockPrivate())
{
}

SpinLock::~SpinLock()
{
	unlock();
	delete d;
}

void SpinLock::lock()
{
	//int sleepMs = 1;
	while (d->val.exchange(true) == true)
	{
		// Try again, until somebody else changes the value to 0,
		// with a call to "unlock()".
		//std::this_thread::sleep_for(std::chrono::milliseconds(std::min(10, sleepMs++)));
	}
}

void SpinLock::unlock()
{
	d->val.exchange(false);
}

bool SpinLock::tryLock()
{
	return d->val.exchange(true) == false;
}

HL_NAMESPACE_END
