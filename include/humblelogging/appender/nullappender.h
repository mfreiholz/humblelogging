#ifndef HL_NULLAPPENDER_H
#define HL_NULLAPPENDER_H

#include "humblelogging/appender.h"

HL_NAMESPACE_BEGIN

class HUMBLE_EXPORT_API NullAppender
	: public Appender
{
public:
	NullAppender();
	virtual ~NullAppender();
	virtual void log(const LogEvent& logEvent);
};

HL_NAMESPACE_END
#endif
