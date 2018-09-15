#ifndef HL_LOGLEVEL_H
#define HL_LOGLEVEL_H

#include "humblelogging/defines.h"
#include <string>

HL_NAMESPACE_BEGIN

class HUMBLE_EXPORT_API LogLevel
{
public:
	enum
	{
		Off,
		Fatal,
		Error,
		Warn,
		Info,
		Debug,
		Trace,
		All
	};

	static std::string resolveLogLevel(int level);
	static int resolveLogLevel(const std::string& logLevel);
};

HL_NAMESPACE_END
#endif
