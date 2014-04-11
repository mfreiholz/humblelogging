#ifndef _LOGGING_LOGLEVEL_HEADER_
#define _LOGGING_LOGLEVEL_HEADER_

#include <string>

#include "humblelogging/defines.h"

namespace humble {
namespace logging {

class HUMBLE_EXPORT_API LogLevel
{
public:
  enum { Off, Fatal, Error, Warn, Info, Debug, Trace, All };

  static std::string resolveLogLevel(int level);
  static int resolveLogLevel(const std::string &logLevel);
};

}}
#endif
