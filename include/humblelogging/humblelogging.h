#ifndef HUMBLELOGGING_HEADER_API
#define HUMBLELOGGING_HEADER_API

#include "appender.h"
#include "appender/consoleappender.h"
#include "appender/fileappender.h"
#include "appender/nullappender.h"
#include "appender/rollingfileappender.h"
#include "configuration.h"
#include "configuration/defaultconfiguration.h"
#include "configuration/simpleconfiguration.h"
#include "factory.h"
#include "formatter.h"
#include "formatter/patternformatter.h"
#include "formatter/simpleformatter.h"
#include "logevent.h"
#include "logger.h"
#include "loglevel.h"

#define HUMBLE_LOGGER(L, N) static humble::logging::Logger& L = humble::logging::Factory::getInstance().getLogger(N)

#ifdef HUMBLE_INCLUDE_PRETTY_FUNCTION
#define HUMBLE_LOG(L, S, LL)                                                       \
	do                                                                             \
	{                                                                              \
		if (L.wouldLog(LL))                                                        \
		{                                                                          \
			humble::logging::LogEvent le(L.getName(), LL, S, __LINE__, __FILE__, __FUNCNAME__); \
			L.log(le);                                                             \
		}                                                                          \
	} while (false)
#else
#define HUMBLE_LOG(L, S, LL)                                                        \
	do                                                                              \
	{                                                                               \
		if (L.wouldLog(LL))                                                         \
		{                                                                           \
			humble::logging::LogEvent le(L.getName(), LL, S, __LINE__, __FILE__, std::string()); \
			L.log(le);                                                              \
		}                                                                           \
	} while (false)
#endif

#define HL_FATAL(L, S) HUMBLE_LOG(L, S, humble::logging::LogLevel::Fatal)
#define HL_ERROR(L, S) HUMBLE_LOG(L, S, humble::logging::LogLevel::Error)
#define HL_WARN(L, S) HUMBLE_LOG(L, S, humble::logging::LogLevel::Warn)
#define HL_INFO(L, S) HUMBLE_LOG(L, S, humble::logging::LogLevel::Info)
#define HL_DEBUG(L, S) HUMBLE_LOG(L, S, humble::logging::LogLevel::Debug)
#define HL_TRACE(L, S) HUMBLE_LOG(L, S, humble::logging::LogLevel::Trace)

#define HL_IF_FATAL(L) L.wouldLog(humble::logging::LogLevel::Fatal)
#define HL_IF_ERROR(L) L.wouldLog(humble::logging::LogLevel::Error)
#define HL_IF_WARN(L) L.wouldLog(humble::logging::LogLevel::Warn)
#define HL_IF_INFO(L) L.wouldLog(humble::logging::LogLevel::Info)
#define HL_IF_DEBUG(L) L.wouldLog(humble::logging::LogLevel::Debug)
#define HL_IF_TRACE(L) L.wouldLog(humble::logging::LogLevel::Trace)

#endif