#ifndef _LOGGING_FACTORY_HEADER_
#define _LOGGING_FACTORY_HEADER_

#include <list>
#include <string>

#include "humblelogging/defines.h"
#include "humblelogging/util/mutex.h"
#include "humblelogging/util/ternarytree.h"

namespace humble {
namespace logging {

class Logger;
class Appender;
class Formatter;
class Configuration;

class HUMBLE_EXPORT_API Factory
{
private:
  Factory();

public:
  ~Factory();

  /*
    Gets the singleton instance of this Factory class.
  */
  static Factory& getInstance();

  /*
    Sets the new Configuration and takes ownership of it.
  */
  Factory& setConfiguration(Configuration *config);

  /*
    Registers a new Appender object and takes ownership of it.
  */
  Factory& registerAppender(Appender *appender);

  /*
    Gets an existing or creates a new Logger object.

    \param[in] name
      The name of the logger. If no Logger with the name exists,
      the method will create a new one automatically.
      Note: The name is case sensitive.

    \return Reference to the existing or created Logger instance.
  */
  Logger& getLogger(const std::string &name);
  
  /*
    Sets the default LogLevel for all new Logger instances.
    
    \param[in] level
      The new default LogLevel.
  */
  Factory& setDefaultLogLevel(int level);
  
  /*
    Sets the default formatter instance to be used by Appenders,
    which does not provide it's own Formatter.
    
    Changing the default Formatter will delete the previously instance.
    
    \param[in] formatter
      The Formatter instance to be used as default.
  */
  Factory& setDefaultFormatter(Formatter *formatter);
  Formatter* getDefaultFormatter() const;
  
  /*
    Changes the LogLevel of all existing Loggers.
    This function does not change the default LogLevel for new Loggers.
    
    \param[in] level
      The new LogLevel for all existing Loggers.
  */
  Factory& changeGlobalLogLevel(int level);

  /*
    Changes the LogLevel of all existing Loggers, which name's begin with
    <code>prefix</code>.

    \param[in] prefix
      The prefix name of the Loggers.
    \param[in] level
      The new log level for the found Loggers.
  */
  Factory& changeLogLevelRecursive(const std::string &prefix, int level);
  
private:
  /*
    Initializes all Loggers with the default configuration.
    The default logging configuration assigns each Logger to each Appender
    with LogLevel::All.
    
    \pre-condition _mutex.lock()
  */
  void configure();
  
private:
  mutable Mutex _mutex;
  Configuration *_config;
  std::list<Logger*> _loggers;
  TernaryTree<Logger*> _loggersTree;
  std::list<Appender*> _appenders;
  Formatter *_defaultFormatter;
  int _level;
};

}}  // End of namespace.
#endif
