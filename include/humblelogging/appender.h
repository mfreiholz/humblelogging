#ifndef _LOGGING_APPENDER_HEADER_
#define _LOGGING_APPENDER_HEADER_

#include <string>
#include <fstream>

#include "humblelogging/defines.h"
#include "humblelogging/logevent.h"
#include "humblelogging/util/mutex.h"

namespace humble {
namespace logging {

class Formatter;

/*
  Base class for all appenders.

  <b>Subclassing</b>
  Call to the protected member "_formatter" should always be locked
  with the local "_mutex".

  \thread-safe
*/
class HUMBLE_EXPORT_API Appender
{
public:
  Appender();
  virtual ~Appender();
  
  /*
    Sets the formatter for this Appender.
    The Appender takes ownership of the Formatter.

    Calling Factory::registerAppender() will call this function with
    the default Formatter, if no other Formatter has been set before.
    
    \param[in] formatter
      The new formatter for the Appender.
  */
  void setFormatter(Formatter *formatter);
  Formatter* getFormatter() const;

  virtual void log(const LogEvent &logEvent) = 0;
  
protected:
  mutable Mutex _mutex;
  Formatter *_formatter;
};


class HUMBLE_EXPORT_API NullAppender
  : public Appender
{
public:
  NullAppender();
  virtual ~NullAppender();
  virtual void log(const LogEvent &logEvent);
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
  Mutex _mutex;
  std::ofstream _stream;
  bool _immediate;
};


class HUMBLE_EXPORT_API RollingFileAppender
  : public Appender
{
public:
  RollingFileAppender(const std::string &filename, bool immediate = false, int maxRoll = 5, unsigned long long maxFileSize = 10485760);
  virtual ~RollingFileAppender();
  virtual void log(const LogEvent &logEvent);

protected:
  /*
    Implements the usual roll over behavior.
    Renames files "file.log.1" => "file.log.2", ...

    TODO: We may want to keep the modification time of the old files,
    which currently gets lost through renaming.

    \pre _mutex.lock()

    \return Returns "true" if the file stream is open and can be used for logging.
  */
  bool roll();

private:
  Mutex _mutex;
  std::string _filename;
  bool _immediate;
  int _maxRoll;
  unsigned long long _maxFileSize;

  std::ofstream _stream;
};

}}  // End of namespaces.
#endif
