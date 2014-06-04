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

///////////////////////////////////////////////////////////////////////////////
// NullAppender
///////////////////////////////////////////////////////////////////////////////

NullAppender::NullAppender()
{
}

NullAppender::~NullAppender()
{
}

void NullAppender::log(const LogEvent &logEvent)
{
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
  MutexLockGuard lock(_mutex);
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
  MutexLockGuard lockBase(Appender::_mutex);
  if (!_formatter) {
    return;
  }
  MutexLockGuard lock(FileAppender::_mutex);
  if (_stream.is_open()) {
    _stream << _formatter->format(logEvent);
    if (_immediate) {
      _stream.flush();
    }
  }
}

///////////////////////////////////////////////////////////////////////////////
// RollingFileAppender
///////////////////////////////////////////////////////////////////////////////

RollingFileAppender::RollingFileAppender(const std::string &filename, bool immediate, int maxRoll, unsigned long long maxFileSize)
  : Appender(),
    _filename(filename),
    _immediate(immediate),
    _maxRoll(maxRoll),
    _maxFileSize(maxFileSize)
{
  //MutexLockGuard lock(_mutex);
  roll();
}

RollingFileAppender::~RollingFileAppender()
{
  if (_stream.is_open()) {
    _stream.flush();
    _stream.close();
  }
}

void RollingFileAppender::log(const LogEvent &logEvent)
{
  MutexLockGuard lockBase(Appender::_mutex);
  MutexLockGuard lock(RollingFileAppender::_mutex);
  if (!roll()) {
    return;
  }
  _stream << _formatter->format(logEvent);
  if (_immediate) {
    _stream.flush();
  }
}

bool RollingFileAppender::roll()
{
  if (!_stream.is_open()) {
    _stream.open(_filename.c_str(), std::ios::out | std::ios::app | std::ios::ate);
    if (!_stream.is_open()) {
      return false;
    }
  }
  if (_stream.tellp() < _maxFileSize) {
    return true;
  }
  // Do the roll.
  _stream.flush();
  _stream.close();
  for (int i = _maxRoll; i >= 0; --i) {
    char *oldFileName = new char[_filename.size() + 10];
    sprintf(oldFileName, "%s.%d", _filename.c_str(), i);
    char *newFileName = new char[_filename.size() + 10];
    sprintf(newFileName, "%s.%d", _filename.c_str(), i + 1);

    if (i + 1 > _maxRoll) {
      std::remove(oldFileName);
    } else if (i == 0) {
      std::rename(_filename.c_str(), newFileName);
    } else {
      std::rename(oldFileName, newFileName);
    }
    delete[] oldFileName;
    delete[] newFileName;
  }
  return roll();
}

}}  // End of namespaces.
