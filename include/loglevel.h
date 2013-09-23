#ifndef _LOGGING_LOGLEVEL_HEADER_
#define _LOGGING_LOGLEVEL_HEADER_

#include <string>

namespace humble {
namespace logging {

class LogLevel
{
public:
  enum { Off, Fatal, Error, Info, Debug, Trace, All };

  static std::string resolveLogLevel(int level);
  static int resolveLogLevel(const std::string &logLevel);
};

}}
#endif
