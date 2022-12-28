#include "humblelogging/appender/nullappender.h"
#include "humblelogging/logevent.h"

HL_NAMESPACE_BEGIN

void NullAppender::log(const LogEvent&)
{}

HL_NAMESPACE_END
