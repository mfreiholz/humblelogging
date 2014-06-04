#include "humblelogging/logevent.h"
#include "humblelogging/util/processinfo.h"

namespace humble {
namespace logging {

LogEvent::LogEvent(int level, const std::string &message, int line, const std::string &file)
  : _level(level),
    _message(message),
    _line(line),
    _file(file),
    _time(time(NULL)),
    _pid(ProcessInfo::getProcessID())
{
}

LogEvent::~LogEvent()
{
}

}}  // End of namespaces.
