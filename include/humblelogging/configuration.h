#ifndef _LOGGING_CONFIGURATOR_HEADER_
#define _LOGGING_CONFIGURATOR_HEADER_

#include <string>

#include "humblelogging/defines.h"
#include "humblelogging/util/ternarytree.h"

namespace humble {
namespace logging {

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
      Not implemented yet!
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
};


class HUMBLE_EXPORT_API FileConfiguration
  : public Configuration
{
public:
  FileConfiguration(const std::string &filepath);
  virtual ~FileConfiguration();
  virtual int getLogLevel(Logger *logger, Appender *appender = 0) const;

private:
  bool load(const std::string &filepath);

private:
  struct Entry {
    std::string pattern;
    bool recursive;
    int level;
  };
  TernaryTree<Entry*> _tree;
};


}}  // End of namespace.
#endif
