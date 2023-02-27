#ifndef HL_PROCESSINFO_H
#define HL_PROCESSINFO_H

#include "humblelogging/defines.h"
#include <cstddef>

HL_NAMESPACE_BEGIN

class HUMBLE_EXPORT_API ProcessInfo
{
public:
	static unsigned int getProcessID();
	static size_t getThreadID();
};

HL_NAMESPACE_END
#endif