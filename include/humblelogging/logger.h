#ifndef HL_LOGGER_H
#define HL_LOGGER_H

#include "humblelogging/defines.h"
#include "humblelogging/logevent.h"
#include "humblelogging/loglevel.h"
#include <list>
#include <memory>
#include <mutex>
#include <string>

HL_NAMESPACE_BEGIN

class Appender;

class HUMBLE_EXPORT_API Logger final
{
public:
	Logger(const std::string& name, int level = LogLevel::Off);
	Logger(const Logger&) = delete;
	Logger& operator=(const Logger&) = delete;
	~Logger();

	Logger& setName(const std::string& name);
	const std::string& getName() const;

	Logger& setLogLevel(int level);
	int getLogLevel() const;

	Logger& addAppender(std::shared_ptr<Appender> appender);
	std::list<std::shared_ptr<Appender>> getAppenders() const;
	bool hasAppender(std::shared_ptr<Appender> appender);

	bool wouldLog(int level) const;
	Logger& log(const LogEvent& logEvent);

private:
	mutable std::mutex _mutex;

	/*
		Name of this logger
	*/
	std::string _name;

	/*
		Log level of this logger
	*/
	int _level;

	/*
		List of all appenders, which are used by the current Logger object.
	*/
	std::list<std::shared_ptr<Appender>> _appenders;
};

HL_NAMESPACE_END
#endif