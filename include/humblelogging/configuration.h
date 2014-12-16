#ifndef _LOGGING_CONFIGURATOR_HEADER_
#define _LOGGING_CONFIGURATOR_HEADER_

#include <string>

#include "humblelogging/defines.h"
#include "humblelogging/util/patternconfigregistry.h"

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
  virtual ~Configuration();

  /*
    Gets the log level for a specific logger/appender pair.

    \param logger
      The Logger instance.
    \param appender
      Not implemented yet! May be useful for later.
  */
  virtual int getLogLevel(Logger *logger, Appender *appender = 0) const = 0;
};


class HUMBLE_EXPORT_API DefaultConfiguration
  : public Configuration
{
public:
  DefaultConfiguration();
  virtual ~DefaultConfiguration();
  virtual int getLogLevel(Logger *logger, Appender *appender = 0) const;

  bool loadFromFile(const std::string &filepath);
  bool loadFromString(const std::string &buffer);

  static DefaultConfiguration* createFromFile(const std::string &filepath);
  static DefaultConfiguration* createFromString(const std::string &buffer);

private:
  PatternConfigRegistry _registry;
};

HL_NAMESPACE_END
#endif
