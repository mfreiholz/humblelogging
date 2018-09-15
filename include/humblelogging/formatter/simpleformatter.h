#ifndef HL_SIMPLEFORMATTER_H
#define HL_SIMPLEFORMATTER_H

#include "humblelogging/formatter.h"

HL_NAMESPACE_BEGIN

/*
  SimpleFormatter formats messages in a fixed predefined format.
  It is maintained and updated during the development process of the
  library to always contain the newest information.
*/
class HUMBLE_EXPORT_API SimpleFormatter
	: public Formatter
{
public:
	SimpleFormatter();
	virtual ~SimpleFormatter();
	virtual Formatter* copy() const;
	virtual std::string format(const LogEvent& logEvent) const;
};

HL_NAMESPACE_END
#endif