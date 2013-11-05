#ifndef _LOGGING_API_HEADER_
#define _LOGGING_API_HEADER_

#include "appender.h"
#include "factory.h"
#include "logger.h"
#include "loglevel.h"

#define HUMBLE_LOGGER(L, N) static humble::logging::Logger& L = humble::logging::Factory::getInstance().getLogger(N)

#define HUMBLE_LOG(L,S,LL) \
  do { \
    if (L.getLogLevel() >= LL) \
      L.log(LL, S); \
  } \
  while (false)

#define HL_FATAL(L,S) HUMBLE_LOG(L, S, humble::logging::LogLevel::Fatal)
#define HL_ERROR(L,S) HUMBLE_LOG(L, S, humble::logging::LogLevel::Error)
#define HL_WARN(L,S)  HUMBLE_LOG(L, S, humble::logging::LogLevel::Warn)
#define HL_INFO(L,S)  HUMBLE_LOG(L, S, humble::logging::LogLevel::Info)
#define HL_DEBUG(L,S) HUMBLE_LOG(L, S, humble::logging::LogLevel::Debug)
#define HL_TRACE(L,S) HUMBLE_LOG(L, S, humble::logging::LogLevel::Trace)

#endif
