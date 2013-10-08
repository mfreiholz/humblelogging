#include "factory.h"

#include <list>
#include <string>
#include <algorithm>

#include "logger.h"
#include "appender.h"
#include "loglevel.h"

namespace humble {
namespace logging {

Factory::Factory()
  : _level(LogLevel::All)
{
}

Factory::~Factory()
{
  std::lock_guard<std::mutex> lock(_mutex);
  while (!_loggers.empty()) {
    Logger *l = _loggers.front();
    _loggers.pop_front();
    delete l;
  }
  while (!_appenders.empty()) {
    Appender *a = _appenders.front();
    _appenders.pop_front();
    delete a;
  }
}

Factory& Factory::getInstance()
{
  static Factory _instance;
  return _instance;
}

Factory& Factory::registerAppender(Appender *appender)
{
  std::lock_guard<std::mutex> lock(_mutex);
  _appenders.push_back(appender);
  configure();
  return (*this);
}

Logger& Factory::getLogger(const std::string &name)
{
  std::lock_guard<std::mutex> lock(_mutex);
  Logger *l = 0;
  for (std::list<Logger*>::iterator i = _loggers.begin(); i != _loggers.end(); ++i) {
    if ((*i)->getName().compare(name) == 0) {
      l = (*i);
      break;
    }
  }
  if (l == 0) {
    l = new Logger(name);
    _loggers.push_back(l);
    configure();
  }
  return (*l);
}

Factory& Factory::setGlobalLevel(int level)
{
  std::lock_guard<std::mutex> lock(_mutex);
  _level = level;
  configure();
  return *this;
}

void Factory::configure()
{
  for (std::list<Logger*>::iterator i = _loggers.begin(); i != _loggers.end(); ++i) {
    (*i)->setLogLevel(LogLevel::All);
    for (std::list<Appender*>::iterator a = _appenders.begin(); a != _appenders.end(); ++a) {
      if ((*i)->hasAppender((*a)))
        continue;
      (*i)->addAppender((*a));
    }
  }
}

}}  // End of namespaces.
