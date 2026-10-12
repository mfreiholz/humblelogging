#include "humblelogging/appender/rollingfileappender.h"
#include "humblelogging/formatter.h"

HL_NAMESPACE_BEGIN

RollingFileAppender::RollingFileAppender(const std::string& filename, bool immediate, int maxRoll, uint64_t maxFileSize)
	: Appender()
	, _filename(filename)
	, _immediate(immediate)
	, _maxRoll(maxRoll)
	, _maxFileSize(maxFileSize)
{
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
	std::lock_guard lock(Appender::_mutex);
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
	if (static_cast<uint64_t>(fpos) < _maxFileSize)
	{
		return true;
	}

	// Do the roll (exactly once, no recursion).
	_stream.flush();
	_stream.close();

	const auto rolledName = [this](int i) { return _filename + "." + std::to_string(i); };

	std::ios::openmode reopenMode = std::ios::out | std::ios::app | std::ios::ate;
	if (_maxRoll > 0)
	{
		// Drop the oldest, shift file.N-1 -> file.N ... file.1 -> file.2
		std::remove(rolledName(_maxRoll).c_str());
		for (int i = _maxRoll - 1; i >= 1; --i)
		{
			std::rename(rolledName(i).c_str(), rolledName(i + 1).c_str());
		}
		// Current file -> file.1
		if (std::rename(_filename.c_str(), rolledName(1).c_str()) == 0)
		{
			reopenMode = std::ios::out | std::ios::trunc;
		}
		// If the rename failed we reopen in append mode: the file stays
		// oversized and we simply try again on the next log() call.
	}
	else
	{
		// No backups configured: start the file over.
		reopenMode = std::ios::out | std::ios::trunc;
	}

	_stream.open(_filename.c_str(), reopenMode);
	return _stream.is_open();
}

HL_NAMESPACE_END