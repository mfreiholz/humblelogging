#ifndef HL_DEFAULTCONFIGURATION_H
#define HL_DEFAULTCONFIGURATION_H

#include <string>

#include "humblelogging/configuration.h"
#include "humblelogging/util/patternconfigregistry.h"

HL_NAMESPACE_BEGIN

class HUMBLE_EXPORT_API DefaultConfiguration
	: public Configuration
{
public:
	DefaultConfiguration();
	virtual ~DefaultConfiguration();
	virtual int getLogLevel(Logger* logger, Appender* appender = 0) const;

	bool loadFromFile(const std::string& filepath);
	bool loadFromString(const std::string& buffer);

	static DefaultConfiguration* createFromFile(const std::string& filepath);
	static DefaultConfiguration* createFromString(const std::string& buffer);

private:
	PatternConfigRegistry _registry;
};

HL_NAMESPACE_END
#endif