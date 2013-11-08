#ifndef _LOGGING_APPENDER_HEADER_
#define _LOGGING_APPENDER_HEADER_

#include <string>
#include <fstream>

#include "defines.h"
#include "logevent.h"
#include "mutex.h"

namespace humble {
namespace logging {

class Formatter;

class HUMBLE_EXPORT_API Appender
{
public:
  Appender();
  virtual ~Appender();
  
  /*
    Sets the formatter for this Appender.
    The Appender takes ownership of the Formatter.
    
    \param[in] formatter
      The new formatter for the Appender.
  */
  void setFormatter(Formatter *formatter);
  
  /*
    Gets the current formatter of the Appender.
    
    \return Formatter
  */
  Formatter* getFormatter() const;

  virtual void log(const LogEvent &logEvent) = 0;
  
protected:
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
  std::mutex _mutex;
  std::ofstream _stream;
  bool _immediate;
};

}}  // End of namespaces.
#endif
