#ifndef HL_FACTORY_H
#define HL_FACTORY_H

#include <list>
#include <string>

#include "humblelogging/defines.h"
#include "humblelogging/util/mutex.h"
#include "humblelogging/util/ternarytree.h"

HL_NAMESPACE_BEGIN

class Logger;
class Appender;
class Formatter;
class Configuration;

/*
  \class Factory

  Base class to manage logging with HumbleLogging.
  Factory class is completely thread-safe and can be called from
  anywhere at anytime.
*/
class HUMBLE_EXPORT_API Factory
{
private:
	Factory();
	Factory(const Factory&);
	Factory& operator=(const Factory&);

public:
	~Factory();

	/*
    Gets the singleton instance of this Factory class.
  */
	static Factory& getInstance();

	/*
    Sets the new Configuration and takes ownership of it.
    Deletes the previously used configuration.

    \param[in] config
      The new configuration to use.
      Note: It's not valid to pass a NULL pointer!

    \return Reference to the Factory itself.
  */
	Factory& setConfiguration(Configuration* config);

	/*
    Registers a new Appender object and takes ownership of it.

    \param[in] appender
      The new Appender to make available for all Loggers.
      Factory takes ownership of the Appender.

    \return Reference to the Factory itself.
  */
	Factory& registerAppender(Appender* appender);

	/*
    Gets an existing or creates a new Logger object.

    \param[in] name
      The name of the logger. If no Logger with the name exists,
      the method will create a new one automatically.
      Note: The name is case sensitive.

    \return Reference to the existing or just created Logger instance.
  */
	Logger& getLogger(const std::string& name);

	/*
    Sets the default formatter instance to be used by Appenders,
    which does not provide it's own Formatter.

    Changing the default Formatter will delete the previously instance.

    \param[in] formatter
      The Formatter instance to be used as default.

    \return Reference to the Factory itself.
  */
	Factory& setDefaultFormatter(Formatter* formatter);
	Formatter* getDefaultFormatter() const;

private:
	/*
    Runs the reconfiguration of all known Loggers and registered Appenders.

    \pre-condition _mutex.lock()
  */
	void configure();

private:
	mutable Mutex _mutex;
	Configuration* _config;
	std::list<Logger*> _loggers;
	TernaryTree<Logger*> _loggersTree;
	std::list<Appender*> _appenders;
	Formatter* _defaultFormatter;
};

HL_NAMESPACE_END
#endif