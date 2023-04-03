#ifndef HL_NULLAPPENDER_H
#define HL_NULLAPPENDER_H

#include "humblelogging/appender.h"

HL_NAMESPACE_BEGIN

/*
	The NullAppender's main use case is performance testing.
	It simply does nothing at all in its `log(...)` implementation.
*/
class HUMBLE_EXPORT_API NullAppender
	: public Appender
{
public:
	void log(const LogEvent& logEvent) override;
};

HL_NAMESPACE_END
#endif