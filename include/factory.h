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
};

}}  // End of namespaces.
#endif
