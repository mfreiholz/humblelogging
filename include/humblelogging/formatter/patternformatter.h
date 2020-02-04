#ifndef HL_PATTERNFORMATTER_H
#define HL_PATTERNFORMATTER_H

#include "humblelogging/formatter.h"

HL_NAMESPACE_BEGIN

/*
  Formats the log entry by a defined pattern.

  Available placeholders:
    %name     = Logger name
    %lls      = Log level as string
    %m        = Log message
    %line     = Line
    %file     = File name
    %filename = Only the file's name (last part of the absolute path)
    %date     = Log date time (format=2013-12-24 12:46:00)

  A nice pattern to open it as .tab/.csv file would be:
    %date\t%lls\t%name\t%filename:%line\t%m\n
*/
class HUMBLE_EXPORT_API PatternFormatter
	: public Formatter
{
public:
	PatternFormatter(const std::string& pattern);
	PatternFormatter(const PatternFormatter& other);
	virtual ~PatternFormatter();
	virtual Formatter* copy() const;
	virtual std::string format(const LogEvent& logEvent) const;

private:
	std::string _pattern;
};

HL_NAMESPACE_END
#endif