#ifndef HL_APPENDER_H
#define HL_APPENDER_H

#include "humblelogging/defines.h"
#include "humblelogging/util/mutex.h"
#include <string>

HL_NAMESPACE_BEGIN

class Formatter;
class LogEvent;

/*
	Base class for all appenders.

	<b>Subclassing</b>
	Call to the protected member "_formatter" should always be locked
	with the local "_mutex".

	\thread-safe
*/
class HUMBLE_EXPORT_API Appender
{
public:
	Appender();
	Appender(const Appender&) = delete;
	Appender& operator=(const Appender&) = delete;
	virtual ~Appender();

	/*
		Sets the formatter for this Appender.
		The Appender takes ownership of the Formatter.

		Calling Factory::registerAppender() will call this function with
		the default Formatter, if no other Formatter has been set before.

		\param[in] formatter
			The new formatter for the Appender.
  */
	void setFormatter(Formatter* formatter);
	Formatter* getFormatter() const;

	virtual void log(const LogEvent& logEvent) = 0;

protected:
	mutable Mutex _mutex;
	Formatter* _formatter;

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
