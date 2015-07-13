#include "humblelogging/configuration/simpleconfiguration.h"

HL_NAMESPACE_BEGIN

SimpleConfiguration::SimpleConfiguration(int level) :
  _level(level)
{
}

SimpleConfiguration::~SimpleConfiguration()
{
}

int SimpleConfiguration::getLogLevel(Logger *logger, Appender *appender) const
{
  return _level;
}

HL_NAMESPACE_END