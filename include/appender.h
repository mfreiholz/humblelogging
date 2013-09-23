#ifndef _LOGGING_APPENDER_HEADER_
#define _LOGGING_APPENDER_HEADER_

#include <string>
#include <fstream>

#include "mutex.h"

namespace humble {
namespace logging {

class Appender
{
public:
  Appender();
  virtual ~Appender();
  virtual void log(int level, const std::string &message) = 0;
};

class ConsoleAppender
  : public Appender
{
public:
  ConsoleAppender();
  virtual ~ConsoleAppender();
  virtual void log(int level, const std::string &message);
};

class FileAppender
  : public Appender
{
public:
  FileAppender(const std::string &filename, bool immediate = false);
  virtual ~FileAppender();
  virtual void log(int level, const std::string &message);
private:
  std::mutex _mutex;
  std::ofstream _stream;
  bool _immediate;
};

}}  // End of namespaces.
#endif
