#ifndef _LOGGING_FORMATTER_HEADER_
#define _LOGGING_FORMATTER_HEADER_

#include <string>

#include "humblelogging/defines.h"
#include "humblelogging/logevent.h"

namespace humble {
namespace logging {

/*
  Base class for all Formatters.
  A Formatter should never necessarily thread-safe.
  It gets copied for each appender, which wants to use the Formatter.
*/
class HUMBLE_EXPORT_API Formatter
{
public:
  Formatter();
  virtual ~Formatter();
  virtual Formatter* copy() const = 0;
  virtual std::string format(const LogEvent &logEvent) const = 0;
};

/*
  Formats messages in a fixed predefined format.
*/
class HUMBLE_EXPORT_API SimpleFormatter
  : public Formatter
{
public:
  SimpleFormatter();
  virtual ~SimpleFormatter();
  virtual Formatter* copy() const;
  virtual std::string format(const LogEvent &logEvent) const;
};

/*
  Formats the log entry by a defined pattern.
  
  Available placeholders:
    %lls      = Log level as string
    %m        = Log message
    %line     = Line
    %file     = File name
    %filename = Only the file's name (last part of the absolute path)
    %date     = Log date time (format=2013-12-24 12:46:00)
*/
class HUMBLE_EXPORT_API PatternFormatter
  : public Formatter
{
public:
  PatternFormatter(const std::string &pattern);
  PatternFormatter(const PatternFormatter &other);
  virtual ~PatternFormatter();
  virtual Formatter* copy() const;
  virtual std::string format(const LogEvent &logEvent) const;
  
private:
  std::string _pattern;
};

}}  // End of namespaces.
#endif
