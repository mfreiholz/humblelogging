#ifndef HL_FORMATTER_H
#define HL_FORMATTER_H

#include "humblelogging/defines.h"
#include <memory>
#include <string>

HL_NAMESPACE_BEGIN

class LogEvent;

/*
	Base class for all Formatters.
	Thread-safty is usually not required, because each appender will have its own Formatter.
*/
class HUMBLE_EXPORT_API Formatter
{
public:
	virtual ~Formatter();
	virtual std::unique_ptr<Formatter> clone() const = 0;
	virtual std::string format(const LogEvent& logEvent) const = 0;
};

HL_NAMESPACE_END
#endif