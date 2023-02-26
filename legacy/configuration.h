#ifndef HL_CONFIGURATION_H
#define HL_CONFIGURATION_H

#include "humblelogging/defines.h"

HL_NAMESPACE_BEGIN

class Logger;
class Appender;

/*
  Base class for all configurations.

  The Configuration is used by the Factory as lookup object,
  to setup specific objects (Loggers, Appenders, ...)
*/
class HUMBLE_EXPORT_API Configuration
{
public:
	Configuration();
	Configuration(const Configuration&) = delete;
	Configuration& operator=(const Configuration&) = delete;
	virtual ~Configuration();

	/*
		Gets the log level for a specific logger/appender pair.

		\param logger
			The Logger instance.
		\param appender
			Not implemented yet! May be useful for later.
	*/
	virtual int getLogLevel(Logger* logger, Appender* appender = 0) const = 0;
};

HL_NAMESPACE_END
#endif