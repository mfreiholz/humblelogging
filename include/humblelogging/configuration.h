#ifndef HL_CONFIGURATION_H
#define HL_CONFIGURATION_H

#include "humblelogging/configuration.h"
#include "humblelogging/util/patternconfigregistry.h"
#include <string>

HL_NAMESPACE_BEGIN

class Logger;
class Appender;

/*
	\class Configuration
	\brief Manages log level configuration of logging engine.

	__Config File Syntax:__
	```
	logger.level(<LOGGER-NAME>[*])=<LOG-LEVEL>
	```
	The asterix (\*) is used to indicate recursive behavior.

	__Config File Example:__
	```
	logger.level(*)=fatal
	logger.level(core.network*)=error
	logger.level(core.network.tcp*)=debug
	```
	Valid values for LOG-LEVEL: `off`, `fatal`, `error`, `info`, `debug`, `trace`, `all`
*/
class HUMBLE_EXPORT_API Configuration final
{
public:
	Configuration();
	Configuration(int level);
	Configuration(const Configuration&) = delete;
	Configuration& operator=(const Configuration&) = delete;
	~Configuration();

	/*
		Initializes configuration by single LogLevel.

		\param[in] level
			LogLevel for all Loggers.
	*/
	void setupFromLogLevel(int level);

	/*
		TODO
	*/
	bool loadFromFile(const std::string& filepath);

	/*
		TODO
	*/
	bool loadFromString(const std::string& buffer);

	/*
		Gets the log level for a specific logger/appender pair.

		\param logger
			The Logger instance.
		\param appender
			Not implemented yet! May be useful for later.
	*/
	int getLogLevel(Logger* logger, Appender* appender = 0) const;

	/*
		Gets the log level for a specific logger/appender pair.

		\param loggerName
			Name of the Logger.
		\param appender
			Not implemented yet! May be useful for later.
	*/
	int getLogLevel(const std::string& loggerName, Appender* appender = 0) const;

private:
	PatternConfigRegistry _registry;
};

HL_NAMESPACE_END
#endif