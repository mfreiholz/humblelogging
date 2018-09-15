#ifndef HL_MUTEX_H
#define HL_MUTEX_H

#include "humblelogging/defines.h"

HL_NAMESPACE_BEGIN

class MutexPrivate;
class HUMBLE_EXPORT_API Mutex
{
	friend class MutexPrivate;
	MutexPrivate* d;

public:
	Mutex();
	~Mutex();
	void lock();
	void unlock();
};

class HUMBLE_EXPORT_API MutexLockGuard
{
public:
	MutexLockGuard(Mutex& lockable)
		: _lockable(lockable)
	{
		_lockable.lock();
	}

	~MutexLockGuard()
	{
		_lockable.unlock();
	}

private:
	Mutex& _lockable;
};

HL_NAMESPACE_END
#endif
