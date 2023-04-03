#ifndef HL_SIMPLEFORMATTER_H
#define HL_SIMPLEFORMATTER_H

#include "humblelogging/formatter.h"
#include <memory>

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
	SimpleFormatter(const SimpleFormatter& other);
	std::unique_ptr<Formatter> clone() const override;
	std::string format(const LogEvent& logEvent) const override;
};

HL_NAMESPACE_END
#endif