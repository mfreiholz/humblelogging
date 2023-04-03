#include "humblelogging/logger.h"
#include "humblelogging/appender.h"
#include <iostream>
#include <list>
#include <string>

HL_NAMESPACE_BEGIN

Logger::Logger(const std::string& name, int level)
	: _name(name)
	, _level(level)
	, _appenders()
{
}

Logger::~Logger()
{
	_appenders.clear();
}

Logger& Logger::setName(const std::string& name)
{
	std::lock_guard lock(_mutex);
	_name = name;
	return (*this);
}

const std::string& Logger::getName() const
{
	std::lock_guard lock(_mutex);
	return _name;
}

Logger& Logger::setLogLevel(int level)
{
	std::lock_guard lock(_mutex);
	_level = level;
	return (*this);
}

int Logger::getLogLevel() const
{
	std::lock_guard lock(_mutex);
	return _level;
}

Logger& Logger::addAppender(std::shared_ptr<Appender> appender)
{
	std::lock_guard lock(_mutex);
	_appenders.push_back(appender);
	return (*this);
}

std::list<std::shared_ptr<Appender>> Logger::getAppenders() const
{
	std::lock_guard lock(_mutex);
	return _appenders;
}

bool Logger::hasAppender(std::shared_ptr<Appender> appender)
{
	std::lock_guard lock(_mutex);
	for (auto i = _appenders.begin(), e = _appenders.end(); i != e; ++i)
	{
		if (*i == appender)
			return true;
	}
	return false;
}

bool Logger::wouldLog(int level) const
{
	std::lock_guard lock(_mutex);
	if (_level >= level /* && !_appenders.empty()*/)
	{
		return true;
	}
	return false;
}

Logger& Logger::log(const LogEvent& logEvent)
{
	std::lock_guard lock(_mutex);
	//if (_level >= logEvent.getLogLevel()) {
	for (auto i = _appenders.begin(), e = _appenders.end(); i != e; ++i)
	{
		(*i)->log(logEvent);
	}
	//}
	return (*this);
}

HL_NAMESPACE_END
