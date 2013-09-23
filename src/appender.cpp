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

void ConsoleAppender::log(int level, const std::string &message)
{
  time_t rawtime = time(NULL);
  struct tm *timeinfo = localtime(&rawtime);
  char timeString [80];
  strftime(timeString, 80, "%Y-%m-%d %H:%M:%S", timeinfo);

  std::string logLevelString = LogLevel::resolveLogLevel(level);
  std::cout
    << "[" << timeString << "] "
    << "[" << logLevelString << "] "
    << message
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

void FileAppender::log(int level, const std::string &message)
{
  if (_stream.is_open()) {
    std::string logLevelString = LogLevel::resolveLogLevel(level);
    _stream << "[" << logLevelString << "] " << message << "\n";
    if (_immediate) {
      _stream.flush();
    }
  }
}

}}  // End of namespaces.
