#include "appender.h"

#include <string>
#include <iostream>
#include <fstream>
#include <ctime>

#include "loglevel.h"
#include "formatter.h"

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
  if (_formatter) {
    delete _formatter;
    _formatter = NULL;
  }
  _formatter = formatter;
}

Formatter* Appender::getFormatter() const
{
  return _formatter;
}

///////////////////////////////////////////////////////////////////////////////
// ConsoleAppender
///////////////////////////////////////////////////////////////////////////////

ConsoleAppender::ConsoleAppender()
  : Appender()
{
}

ConsoleAppender::~ConsoleAppender()
{
}

void ConsoleAppender::log(const LogEvent &logEvent)
{
  if (!_formatter) {
    return;
  }
  std::cout << _formatter->format(logEvent);
}

///////////////////////////////////////////////////////////////////////////////
// FileAppender
///////////////////////////////////////////////////////////////////////////////

FileAppender::FileAppender(const std::string &filename, bool immediate)
  : Appender(), _stream(), _immediate(immediate)
{
  _stream.open(filename.c_str(), std::ios::out | std::ios::app);
}

FileAppender::~FileAppender()
{
  if (_stream.is_open()) {
    _stream.flush();
    _stream.close();
  }
}

void FileAppender::log(const LogEvent &logEvent)
{
  if (!_formatter) {
    return;
  }
  std::lock_guard<std::mutex> lock(_mutex);
  if (_stream.is_open()) {
    _stream << _formatter->format(logEvent);
    if (_immediate) {
      _stream.flush();
    }
  }
}

}}  // End of namespaces.
