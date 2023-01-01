#ifndef HL_APPENDER_H
#define HL_APPENDER_H

#include "humblelogging/defines.h"
#include <memory>
#include <mutex>
#include <string>

HL_NAMESPACE_BEGIN

class Formatter;
class LogEvent;

/*!
	\brief Appenders shows or stores log-events to different locations.

	__Thread-Safety / Subclasses:__ Access to local members should always be protected with `Appender::_mutex`.
*/
class HUMBLE_EXPORT_API Appender
{
public:
	Appender();
	Appender(const Appender&) = delete;
	Appender& operator=(const Appender&) = delete;
	virtual ~Appender();

	/*!
		Sets the formatter for this Appender.
		The Appender takes ownership of the Formatter.

		Calling Factory::registerAppender() will call this function with
		the default Formatter.

		\param[in] formatter
			The new formatter for the Appender.
	*/
	void setFormatter(std::unique_ptr<Formatter> formatter);

	/*!
		This function is called whenever one of the logging macros is used.
		\see HL_INFO
	*/
	virtual void log(const LogEvent& logEvent) = 0;

protected:
	mutable std::mutex _mutex;
	std::unique_ptr<Formatter> _formatter;

	/*
		Formats the `logEvent` with current assigned `_formatter`.
		This function makes sure to have `_mutex` locked and unlocked.
		In case you need to lock for a longer time, you should call
		`_formatter->format(...)` within your own lock of `_mutex`.
	*/
	std::string format(const LogEvent& logEvent) const;
};

HL_NAMESPACE_END
#endif