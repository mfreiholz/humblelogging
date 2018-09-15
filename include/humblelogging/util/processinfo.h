#ifndef HL_PROCESSINFO_H
#define HL_PROCESSINFO_H

#include "humblelogging/defines.h"

HL_NAMESPACE_BEGIN

class HUMBLE_EXPORT_API ProcessInfo
{
public:
	static unsigned int getProcessID();
	static unsigned int getThreadID();
};

HL_NAMESPACE_END
#endif
