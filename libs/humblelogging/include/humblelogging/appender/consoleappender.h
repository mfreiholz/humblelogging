#ifndef HL_CONSOLEAPPENDER_H
#define HL_CONSOLEAPPENDER_H

#include "humblelogging/appender.h"

HL_NAMESPACE_BEGIN

/*
	\brief Writes all log output to std::out.
*/
class HUMBLE_EXPORT_API ConsoleAppender
	: public Appender
{
public:
	void log(const LogEvent& logEvent) override;
};

HL_NAMESPACE_END
#endif