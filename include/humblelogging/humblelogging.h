#ifndef HUMBLELOGGING_HEADER_API
#define HUMBLELOGGING_HEADER_API

#include "appender.h"
#include "appender/consoleappender.h"
#include "appender/fileappender.h"
#include "appender/nullappender.h"
#include "appender/rollingfileappender.h"
#include "configuration.h"
#include "factory.h"
#include "formatter.h"
#include "formatter/patternformatter.h"
#include "formatter/simpleformatter.h"
#include "logevent.h"
#include "logger.h"
#include "loglevel.h"
#include "util/fmt.hpp"

/*
	Defines a static variable with access to a new or existing Logger by its name.
*/
#define HUMBLE_LOGGER(L, N) \
	static auto L = HL_NS::Factory::getInstance().getLogger(N)


// Logs a simple message event.
#define HUMBLE_LOG(L, S, LL)                                                          \
	do                                                                                \
	{                                                                                 \
		if (L->wouldLog(LL))                                                          \
		{                                                                             \
			HL_NS::LogEvent le(L->getName(), LL, S, __LINE__, __FILE__, __FUNCNAME__); \
			L->log(le);                                                               \
		}                                                                             \
	} while (false)


// Logs a formatted message event.
// Suppports same syntax as `printf()`.
#define HUMBLE_LOG_FMT(L, LL, ...)                                                         \
	do                                                                                     \
	{                                                                                      \
		if (L->wouldLog(LL))                                                               \
		{                                                                                  \
			const std::string fmtstr = HL_NS::strfmt(__VA_ARGS__);                         \
			HL_NS::LogEvent le(L->getName(), LL, fmtstr, __LINE__, __FILE__, __FUNCNAME__); \
			L->log(le);                                                                    \
		}                                                                                  \
	} while (false)


#define HL_FATAL(L, S) HUMBLE_LOG(L, S, HL_NS::LogLevel::Fatal)
#define HL_ERROR(L, S) HUMBLE_LOG(L, S, HL_NS::LogLevel::Error)
#define HL_WARN(L, S) HUMBLE_LOG(L, S, HL_NS::LogLevel::Warn)
#define HL_INFO(L, S) HUMBLE_LOG(L, S, HL_NS::LogLevel::Info)
#define HL_DEBUG(L, S) HUMBLE_LOG(L, S, HL_NS::LogLevel::Debug)
#define HL_TRACE(L, S) HUMBLE_LOG(L, S, HL_NS::LogLevel::Trace)

#define HL_FATAL_F(L, ...) HUMBLE_LOG_FMT(L, HL_NS::LogLevel::Fatal, __VA_ARGS__)
#define HL_ERROR_F(L, ...) HUMBLE_LOG_FMT(L, HL_NS::LogLevel::Error, __VA_ARGS__)
#define HL_WARN_F(L, ...) HUMBLE_LOG_FMT(L, HL_NS::LogLevel::Warn, __VA_ARGS__)
#define HL_INFO_F(L, ...) HUMBLE_LOG_FMT(L, HL_NS::LogLevel::Info, __VA_ARGS__)
#define HL_DEBUG_F(L, ...) HUMBLE_LOG_FMT(L, HL_NS::LogLevel::Debug, __VA_ARGS__)
#define HL_TRACE_F(L, ...) HUMBLE_LOG_FMT(L, HL_NS::LogLevel::Trace, __VA_ARGS__)

#define HL_IF_FATAL(L) L.wouldLog(HL_NS::LogLevel::Fatal)
#define HL_IF_ERROR(L) L.wouldLog(HL_NS::LogLevel::Error)
#define HL_IF_WARN(L) L.wouldLog(HL_NS::LogLevel::Warn)
#define HL_IF_INFO(L) L.wouldLog(HL_NS::LogLevel::Info)
#define HL_IF_DEBUG(L) L.wouldLog(HL_NS::LogLevel::Debug)
#define HL_IF_TRACE(L) L.wouldLog(HL_NS::LogLevel::Trace)

#endif