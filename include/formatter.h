#ifndef _LOGGING_FORMATTER_HEADER_
#define _LOGGING_FORMATTER_HEADER_

#include <string>

#include "logevent.h"

namespace humble {
namespace logging {

class Formatter
{
public:
  Formatter();
  ~Formatter();
  virtual std::string format(const LogEvent &logEvent) const = 0;
};


class SimpleFormatter
{
public:
  SimpleFormatter();
  ~SimpleFormatter();
  virtual std::string format(const LogEvent &logEvent) const;
};

}}  // End of namespaces.
#endif
