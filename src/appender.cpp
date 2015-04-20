#include "humblelogging/appender.h"

#include <string>
#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdio>

#include "humblelogging/loglevel.h"
#include "humblelogging/formatter.h"

namespace humble {
namespace logging {

///////////////////////////////////////////////////////////////////////////////
// Appender
///////////////////////////////////////////////////////////////////////////////

Appender::Appender()
  : _formatter(NULL)
{
}

Appender::~Appender()
{
  if (_formatter) {
    delete _formatter;
    _formatter = NULL;
  }
}

void Appender::setFormatter(Formatter *formatter)
{
  MutexLockGuard lock(_mutex);
  if (_formatter) {
    delete _formatter;
    _formatter = NULL;
  }
  _formatter = formatter;
}

Formatter* Appender::getFormatter() const
{
  MutexLockGuard lock(_mutex);
  return _formatter;
}

}}  // End of namespaces.
