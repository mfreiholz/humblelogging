#ifndef _LOGGING_FACTORY_HEADER_
#define _LOGGING_FACTORY_HEADER_

#include <list>
#include <string>

#include "mutex.h"

namespace humble {
namespace logging {

class Logger;
class Appender;

class Factory
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
    Initializes all loggers with correct logging level and assigns
    the correct appender classes to them. This method needs to be called
    everytime when a new appender has been added or a live log level change
    has been made.
  */
  void configure();

  /*
    Registers a new Appender object and takes ownership of it.
    The method returns a reference to the registered appender object.
  */
  Appender& registerAppender(Appender *appender);

  /*
    Gets an existing or creates a new Logger object.
  */
  Logger& getLogger(const std::string &name);
  
private:
  std::mutex _mutex;
  std::list<Logger*> _loggers;
  std::list<Appender*> _appenders;
};

}}  // End of namespaces.
#endif
