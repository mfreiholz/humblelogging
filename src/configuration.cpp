#include "humblelogging/configuration.h"
#include "humblelogging/logger.h"
#include "humblelogging/loglevel.h"
#include <fstream>

HL_NAMESPACE_BEGIN

Configuration::Configuration()
{
	setupFromLogLevel(LogLevel::All);
}

Configuration::Configuration(int level)
{
	setupFromLogLevel(level);
}

Configuration::~Configuration()
{}

void Configuration::setupFromLogLevel(int level)
{
	_registry.loadFromString("logger.level(*)=" + LogLevel::resolveLogLevel(level));
}

bool Configuration::loadFromFile(const std::string& filepath)
{
	return _registry.loadFromFile(filepath);
}

bool Configuration::loadFromString(const std::string& buffer)
{
	return _registry.loadFromString(buffer);
}

int Configuration::getLogLevel(Logger* logger, Appender*) const
{
	return _registry.getLogLevel(logger->getName());
}

HL_NAMESPACE_END