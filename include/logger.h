#ifndef _LOGGER_HEADER_
#define _LOGGER_HEADER_

#include <string>
#include <list>

#include "loglevel.h"

namespace humble {
namespace logging {

class Appender;

class Logger
{
public:
  Logger(const std::string &name, int level = LogLevel::Off);
  ~Logger();

  Logger& setName(const std::string &name);
  const std::string& getName() const;

  Logger& setLogLevel(int level);
  int getLogLevel() const;

  Logger& addAppender(Appender *appender);
  std::list<Appender*> getAppenders() const;

  Logger& log(int level, const std::string &message);
  
private:
  /*
    Name of this logger
  */
  std::string _name;

  /*
    Log level of this logger
  */
  int _level;

  /*
    List of all appenders, which are used by the current Logger object.
  */
  std::list<Appender*> _appenders;
};

}}  // End of namespaces.
#endif
