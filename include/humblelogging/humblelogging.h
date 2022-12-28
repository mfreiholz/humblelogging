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
#include "util/fmt.hpp"

#define HUMBLE_LOGGER(L, N) static humble::logging::Logger& L = humble::logging::Factory::getInstance().getLogger(N)

#ifdef HUMBLE_INCLUDE_PRETTY_FUNCTION

// Logs a simple message event.
#define HUMBLE_LOG(L, S, LL)                                                       \
	do                                                                             \
	{                                                                              \
		if (L.wouldLog(LL))                                                        \
		{                                                                          \
			humble::logging::LogEvent le(L.getName(), LL, S, __LINE__, __FILE__, __FUNCNAME__); \
			L.log(le);                                                             \
		}                                                                          \
	} while (false)

// Logs a formatted message event.
// Suppports same syntax as `printf()`.
#define HUMBLE_LOG_FMT(L, LL, ...) \
	do \
	{ \
		if (L.wouldLog(LL)) \
		{ \
			const std::string fmtstr = strfmt(__VA_ARGS__); \
			humble::logging::LogEvent le(L.getName(), LL, fmtstr, __LINE__, __FILE__, __FUNCNAME__); \
			L.log(le); \
		} \
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
#define HUMBLE_LOG_FMT(L, LL, ...) \
	do \
	{ \
		if (L.wouldLog(LL)) \
		{ \
			const std::string fmtstr = strfmt(__VA_ARGS__); \
			humble::logging::LogEvent le(L.getName(), LL, fmtstr, __LINE__, __FILE__, std::string()); \
			L.log(le); \
		} \
	} while (false)
#endif

#define HL_FATAL(L, S) HUMBLE_LOG(L, S, humble::logging::LogLevel::Fatal)
#define HL_ERROR(L, S) HUMBLE_LOG(L, S, humble::logging::LogLevel::Error)
#define HL_WARN(L, S) HUMBLE_LOG(L, S, humble::logging::LogLevel::Warn)
#define HL_INFO(L, S) HUMBLE_LOG(L, S, humble::logging::LogLevel::Info)
#define HL_DEBUG(L, S) HUMBLE_LOG(L, S, humble::logging::LogLevel::Debug)
#define HL_TRACE(L, S) HUMBLE_LOG(L, S, humble::logging::LogLevel::Trace)

#define HL_FATAL_F(L, ...) HUMBLE_LOG_FMT(L, humble::logging::LogLevel::Fatal, __VA_ARGS__)
#define HL_ERROR_F(L, ...) HUMBLE_LOG_FMT(L, humble::logging::LogLevel::Error, __VA_ARGS__)
#define HL_WARN_F(L, ...) HUMBLE_LOG_FMT(L, humble::logging::LogLevel::Warn, __VA_ARGS__)
#define HL_INFO_F(L, ...) HUMBLE_LOG_FMT(L, humble::logging::LogLevel::Info, __VA_ARGS__)
#define HL_DEBUG_F(L, ...) HUMBLE_LOG_FMT(L, humble::logging::LogLevel::Debug, __VA_ARGS__)
#define HL_TRACE_F(L, ...) HUMBLE_LOG_FMT(L, humble::logging::LogLevel::Trace, __VA_ARGS__)

#define HL_IF_FATAL(L) L.wouldLog(humble::logging::LogLevel::Fatal)
#define HL_IF_ERROR(L) L.wouldLog(humble::logging::LogLevel::Error)
#define HL_IF_WARN(L) L.wouldLog(humble::logging::LogLevel::Warn)
#define HL_IF_INFO(L) L.wouldLog(humble::logging::LogLevel::Info)
#define HL_IF_DEBUG(L) L.wouldLog(humble::logging::LogLevel::Debug)
#define HL_IF_TRACE(L) L.wouldLog(humble::logging::LogLevel::Trace)

#endif