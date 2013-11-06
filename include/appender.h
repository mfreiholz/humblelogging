#ifndef _LOGGING_APPENDER_HEADER_
#define _LOGGING_APPENDER_HEADER_

#include <string>
#include <fstream>

#include "defines.h"
#include "logevent.h"
#include "mutex.h"

namespace humble {
namespace logging {

class HUMBLE_EXPORT_API Appender
{
public:
  Appender();
  virtual ~Appender();
  virtual void log(const LogEvent &logEvent) = 0;
};

class HUMBLE_EXPORT_API ConsoleAppender
  : public Appender
{
public:
  ConsoleAppender();
  virtual ~ConsoleAppender();
  virtual void log(const LogEvent &logEvent);
};

class HUMBLE_EXPORT_API FileAppender
  : public Appender
{
public:
  FileAppender(const std::string &filename, bool immediate = false);
  virtual ~FileAppender();
  virtual void log(const LogEvent &logEvent);

private:
  std::mutex _mutex;
  std::ofstream _stream;
  bool _immediate;
};

}}  // End of namespaces.
#endif
