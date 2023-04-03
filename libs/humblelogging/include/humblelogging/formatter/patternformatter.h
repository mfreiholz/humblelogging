#ifndef HL_PATTERNFORMATTER_H
#define HL_PATTERNFORMATTER_H

#include "humblelogging/formatter.h"
#include <memory>
#include <string>

HL_NAMESPACE_BEGIN

/*
	Formats the log entry by a defined pattern.

	Available placeholders:
		%name     = Logger name
		%lls      = Log level as string
		%m        = Log message
		%line     = Line
		%pid      = Process ID
		%tid      = Thread ID
		%filename = Only the file's name (last part of the absolute path)
		%file     = Absolute file path during compile time.
		%func     = Signature of the current function.
		%date     = Log date time (format=2013-12-24 12:46:00)

	A nice pattern to open it as .tab/.csv file would be:
		%date\t%lls\t%name\t%filename:%line\t%m\n
*/
class HUMBLE_EXPORT_API PatternFormatter
	: public Formatter
{
public:
	PatternFormatter(const std::string& pattern, const std::string& timePattern = "%Y-%m-%d %H:%M:%S");
	PatternFormatter(const PatternFormatter& other);
	std::unique_ptr<Formatter> clone() const override;
	std::string format(const LogEvent& logEvent) const override;

private:
	std::string _pattern;
	std::string _timePattern;
};

HL_NAMESPACE_END
#endif