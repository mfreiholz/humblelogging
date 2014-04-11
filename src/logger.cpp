#include "humblelogging/logger.h"

#include <string>
#include <list>
#include <iostream>

#include "humblelogging/appender.h"

namespace humble {
namespace logging {

Logger::Logger(const std::string &name, int level)
  : _name(name), _level(level), _appenders()
{ 

}

Logger::~Logger()
{
  _appenders.clear();
}

Logger& Logger::setName(const std::string &name)
{
  MutexLockGuard lock(_mutex);
  _name = name;
  return (*this);
}

const std::string& Logger::getName() const
{
  MutexLockGuard lock(_mutex);
  return _name;
}

Logger& Logger::setLogLevel(int level)
{
  MutexLockGuard lock(_mutex);
  _level = level;
  return (*this);
}

int Logger::getLogLevel() const
{
  MutexLockGuard lock(_mutex);
  return _level;
}

Logger& Logger::addAppender(Appender *appender)
{
  MutexLockGuard lock(_mutex);
  _appenders.push_back(appender);
  return (*this);
}

std::list<Appender*> Logger::getAppenders() const
{
  MutexLockGuard lock(_mutex);
  return _appenders;
}

bool Logger::hasAppender(Appender *appender)
{
  MutexLockGuard lock(_mutex);
  for (std::list<Appender*>::iterator i = _appenders.begin(), e = _appenders.end(); i != e; ++i) {
    if (*i == appender)
      return true;
  }
  return false;
}

bool Logger::wouldLog(int level) const
{
  MutexLockGuard lock(_mutex);
  if (_level >= level && !_appenders.empty()) {
    return true;
  }
  return false;
}

Logger& Logger::log(const LogEvent &logEvent)
{
  MutexLockGuard lock(_mutex);
  if (_level >= logEvent.getLogLevel()) {
    for (std::list<Appender*>::iterator i = _appenders.begin(), e = _appenders.end(); i != e; ++i) {
      (*i)->log(logEvent);
    }
  }
  return (*this);
}

}}  // End of namespaces.
