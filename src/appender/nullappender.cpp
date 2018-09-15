#include "humblelogging/appender/nullappender.h"

#include "humblelogging/logevent.h"

HL_NAMESPACE_BEGIN

///////////////////////////////////////////////////////////////////////////////
// NullAppender
///////////////////////////////////////////////////////////////////////////////

NullAppender::NullAppender()
{
}

NullAppender::~NullAppender()
{
}

void NullAppender::log(const LogEvent& logEvent)
{
	(void)logEvent;
}

HL_NAMESPACE_END
