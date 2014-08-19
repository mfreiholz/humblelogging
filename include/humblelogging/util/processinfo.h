#ifndef HUMBLE_PROCESSINFO_HEADER
#define HUMBLE_PROCESSINFO_HEADER

#include "humblelogging/defines.h"

namespace humble {
namespace logging {

class HUMBLE_EXPORT_API ProcessInfo
{
public:
  static unsigned int getProcessID();
  static unsigned int getThreadID();
};

}} // End of namespace.
#endif
