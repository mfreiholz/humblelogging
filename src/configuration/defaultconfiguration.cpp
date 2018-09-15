#include "humblelogging/configuration/defaultconfiguration.h"

#include <fstream>

#include "humblelogging/logger.h"
#include "humblelogging/loglevel.h"

HL_NAMESPACE_BEGIN

DefaultConfiguration::DefaultConfiguration()
	: Configuration()
{
}

DefaultConfiguration::~DefaultConfiguration()
{
}

int DefaultConfiguration::getLogLevel(Logger* logger, Appender*) const
{
	return _registry.getLogLevel(logger->getName());
}

bool DefaultConfiguration::loadFromFile(const std::string& filepath)
{
	return _registry.loadFromFile(filepath);
}

bool DefaultConfiguration::loadFromString(const std::string& buffer)
{
	return _registry.loadFromString(buffer);
}

DefaultConfiguration* DefaultConfiguration::createFromFile(const std::string& filepath)
{
	DefaultConfiguration* config = new DefaultConfiguration();
	if (!config->loadFromFile(filepath))
	{
		delete config;
		return NULL;
	}
	return config;
}

DefaultConfiguration* DefaultConfiguration::createFromString(const std::string& buffer)
{
	DefaultConfiguration* config = new DefaultConfiguration();
	if (!config->loadFromString(buffer))
	{
		delete config;
		return NULL;
	}
	return config;
}

HL_NAMESPACE_END