#include "humblelogging/appender/fileappender.h"
#include "humblelogging/formatter.h"

HL_NAMESPACE_BEGIN

///////////////////////////////////////////////////////////////////////////////
// FileAppender
///////////////////////////////////////////////////////////////////////////////

FileAppender::FileAppender(const std::string& filename, bool immediate)
	: Appender()
	, _stream()
	, _immediate(immediate)
{
	_stream.open(filename.c_str(), std::ios::out | std::ios::app);
}

FileAppender::~FileAppender()
{
	if (_stream.is_open())
	{
		_stream.flush();
		_stream.close();
	}
}

void FileAppender::log(const LogEvent& logEvent)
{
	MutexLockGuard lockBase(Appender::_mutex);
	if (!_formatter)
	{
		return;
	}
	MutexLockGuard lock(FileAppender::_mutex);
	if (_stream.is_open())
	{
		_stream << _formatter->format(logEvent);
		if (_immediate)
		{
			_stream.flush();
		}
	}
}

HL_NAMESPACE_END
