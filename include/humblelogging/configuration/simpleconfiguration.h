#ifndef HL_SIMPLECONFIGURATION_H
#define HL_SIMPLECONFIGURATION_H

#include "humblelogging/configuration.h"
#include "humblelogging/loglevel.h"

HL_NAMESPACE_BEGIN

class HUMBLE_EXPORT_API SimpleConfiguration
	: public Configuration
{
public:
	SimpleConfiguration(int level = LogLevel::All);
	virtual ~SimpleConfiguration();
	virtual int getLogLevel(Logger* logger, Appender* appender = 0) const;

private:
	int _level;
};

HL_NAMESPACE_END
#endif