#ifndef _LOGGING_FORMATTER_HEADER_
#define _LOGGING_FORMATTER_HEADER_

#include <string>

#include "defines.h"
#include "logevent.h"

namespace humble {
namespace logging {

class HUMBLE_EXPORT_API Formatter
{
public:
  Formatter();
  virtual ~Formatter();
  virtual Formatter* copy() const = 0;
  virtual std::string format(const LogEvent &logEvent) const = 0;
};


class HUMBLE_EXPORT_API SimpleFormatter
  : public Formatter
{
public:
  SimpleFormatter();
  virtual ~SimpleFormatter();
  virtual Formatter* copy() const;
  virtual std::string format(const LogEvent &logEvent) const;
};

}}  // End of namespaces.
#endif
