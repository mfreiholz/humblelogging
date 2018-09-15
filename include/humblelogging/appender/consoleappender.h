#ifndef HL_CONSOLEAPPENDER_H
#define HL_CONSOLEAPPENDER_H

#include "humblelogging/appender.h"

HL_NAMESPACE_BEGIN

class HUMBLE_EXPORT_API ConsoleAppender
	: public Appender
{
public:
	ConsoleAppender();
	virtual ~ConsoleAppender();
	virtual void log(const LogEvent& logEvent);
};

HL_NAMESPACE_END
#endif
