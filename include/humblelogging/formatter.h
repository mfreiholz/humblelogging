#ifndef HL_FORMATTER_H
#define HL_FORMATTER_H

#include <string>

#include "humblelogging/defines.h"

HL_NAMESPACE_BEGIN

class LogEvent;

/*
  Base class for all Formatters.
  A Formatter should never necessarily thread-safe.
  It gets copied for each appender, which wants to use the Formatter.
*/
class HUMBLE_EXPORT_API Formatter
{
public:
	Formatter();
	virtual ~Formatter();
	virtual Formatter* copy() const = 0;
	virtual std::string format(const LogEvent& logEvent) const = 0;
};

HL_NAMESPACE_END
#endif
