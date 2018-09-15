#include "humblelogging/appender/rollingfileappender.h"
#include "humblelogging/formatter.h"

HL_NAMESPACE_BEGIN

///////////////////////////////////////////////////////////////////////////////
// RollingFileAppender
///////////////////////////////////////////////////////////////////////////////

RollingFileAppender::RollingFileAppender(const std::string& filename, bool immediate, int maxRoll, unsigned long maxFileSize)
	: Appender()
	, _filename(filename)
	, _immediate(immediate)
	, _maxRoll(maxRoll)
	, _maxFileSize(maxFileSize)
{
	//MutexLockGuard lock(_mutex);
	roll();
}

RollingFileAppender::~RollingFileAppender()
{
	if (_stream.is_open())
	{
		_stream.flush();
		_stream.close();
	}
}

void RollingFileAppender::log(const LogEvent& logEvent)
{
	MutexLockGuard lockBase(Appender::_mutex);
	MutexLockGuard lock(RollingFileAppender::_mutex);
	if (!roll())
	{
		return;
	}
	_stream << _formatter->format(logEvent);
	if (_immediate)
	{
		_stream.flush();
	}
}

bool RollingFileAppender::roll()
{
	if (!_stream.is_open())
	{
		_stream.open(_filename.c_str(), std::ios::out | std::ios::app | std::ios::ate);
		if (!_stream.is_open())
		{
			return false;
		}
	}
	const std::streampos fpos = _stream.tellp();
	if (fpos < 0)
	{
		return false;
	}
	if (static_cast<unsigned long>(fpos) < _maxFileSize)
	{
		return true;
	}
	// Do the roll.
	_stream.flush();
	_stream.close();
	for (int i = _maxRoll; i >= 0; --i)
	{
		char* oldFileName = new char[_filename.size() + 10];
		sprintf(oldFileName, "%s.%d", _filename.c_str(), i);
		char* newFileName = new char[_filename.size() + 10];
		sprintf(newFileName, "%s.%d", _filename.c_str(), i + 1);

		if (i + 1 > _maxRoll)
		{
			std::remove(oldFileName);
		}
		else if (i == 0)
		{
			std::rename(_filename.c_str(), newFileName);
		}
		else
		{
			std::rename(oldFileName, newFileName);
		}
		delete[] oldFileName;
		delete[] newFileName;
	}
	return roll();
}

HL_NAMESPACE_END
