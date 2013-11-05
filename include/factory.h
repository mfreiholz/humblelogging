#ifndef _LOGGING_FACTORY_HEADER_
#define _LOGGING_FACTORY_HEADER_

#include <list>
#include <string>

#include "defines.h"
#include "mutex.h"

namespace humble {
namespace logging {

class Logger;
class Appender;

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
    Registers a new Appender object and takes ownership of it.
    The method returns a reference to the registered appender object.
  */
  Factory& registerAppender(Appender *appender);

  /*
    Gets an existing or creates a new Logger object.

    \param[in] name
      The name of the logger. If no longer with the name exists,
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
    Changes the LogLevel of all existing Loggers.
    This function does not change the default LogLevel for new Loggers.
    
    \param[in] level
      The new LogLevel for all existing Loggers.
  */
  Factory& changeGlobalLogLevel(int level);
  
private:
  /*
    Initializes all Loggers with the default configuration.
    The default logging configuration assigns each Logger to each Appender
    with LogLevel::All.
    
    \pre-condition _mutex.lock()
  */
  void configure();
  
private:
  std::mutex _mutex;
  std::list<Logger*> _loggers;
  std::list<Appender*> _appenders;
  int _level;
};

}}  // End of namespaces.
#endif
