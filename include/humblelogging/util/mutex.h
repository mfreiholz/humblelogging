#ifndef HUMBLE_MUTEX_HEADER
#define HUMBLE_MUTEX_HEADER

#ifdef WIN32
#include "mutex_windows.h"
#else
#include <mutex>
#endif

#endif
