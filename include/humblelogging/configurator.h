#ifndef _LOGGING_CONFIGURATOR_HEADER_
#define _LOGGING_CONFIGURATOR_HEADER_

#include <string>

#include "humblelogging/defines.h"

namespace humble {
namespace logging {

class Logger;

/*
  Base class for all configurators.

  The configurator is used by the Factory as lookup object,
  to setup specific objects (Loggers, Appenders, ...)
*/
class HUMBLE_EXPORT_API Configurator
{
public:
  Configurator();
  virtual ~Configurator();
  virtual void configure(Logger *l) = 0;

protected:
  int _defaultLogLevel;
};


class HUMBLE_EXPORT_API DefaultConfigurator
  : public Configurator
{
public:
  DefaultConfigurator();
  virtual ~DefaultConfigurator();
  virtual void configure(Logger *l);
  
  DefaultConfigurator* fromFile(const std::string &filepath);
};


}}  // End of namespace.
#endif
