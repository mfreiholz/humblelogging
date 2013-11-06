#include "appender.h"

#include <string>
#include <iostream>
#include <fstream>
#include <ctime>

#include "loglevel.h"

namespace humble {
namespace logging {

///////////////////////////////////////////////////////////////////////////////
// Appender
///////////////////////////////////////////////////////////////////////////////

Appender::Appender()
{

}

Appender::~Appender()
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
  time_t rawtime = time(NULL);
  struct tm *timeinfo = localtime(&rawtime);
  char timeString [80];
  strftime(timeString, 80, "%Y-%m-%d %H:%M:%S", timeinfo);

  std::string logLevelString = LogLevel::resolveLogLevel(logEvent.getLogLevel());
  std::cout
    << "[" << timeString << "] "
    << "[" << logLevelString << "] "
    << "[line=" << logEvent.getLine() << "] "
    << "[file=" << logEvent.getFile() << "] "
    << logEvent.getMessage()
    << "\n";
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
  std::string logLevelString = LogLevel::resolveLogLevel(logEvent.getLogLevel());

  time_t rawtime = time(NULL);
  struct tm *timeinfo = localtime(&rawtime);
  char timeString [80];
  strftime(timeString, 80, "%Y-%m-%d %H:%M:%S", timeinfo);

  std::lock_guard<std::mutex> lock(_mutex);
  if (_stream.is_open()) {
    _stream
      << "[" << timeString << "] "
      << "[" << logLevelString << "] "
      << "[line=" << logEvent.getLine() << "] "
      << "[file=" << logEvent.getFile() << "] "
      << logEvent.getMessage()
      << "\n";
    if (_immediate) {
      _stream.flush();
    }
  }
}

}}  // End of namespaces.
