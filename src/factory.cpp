#include "humblelogging/factory.h"
#include "humblelogging/appender.h"
#include "humblelogging/configuration.h"
#include "humblelogging/formatter.h"
#include "humblelogging/formatter/simpleformatter.h"
#include "humblelogging/logger.h"
#include "humblelogging/loglevel.h"
#include "humblelogging/version.h"
#include <algorithm>
#include <cassert>
#include <list>
#include <string>

HL_NAMESPACE_BEGIN

Factory::Factory()
	: _config(std::make_unique<Configuration>())
	, _defaultFormatter(std::make_unique<SimpleFormatter>())
{}

Factory::~Factory()
{}

Factory& Factory::getInstance()
{
	static Factory _instance;
	return _instance;
}

void Factory::setConfiguration(std::unique_ptr<Configuration> config)
{
	assert(config);

	std::lock_guard lock(_mutex);
	_config = std::move(config);
	configure();
}

void Factory::setDefaultFormatter(std::unique_ptr<Formatter> formatter)
{
	assert(formatter);

	std::lock_guard lock(_mutex);
	_defaultFormatter = std::move(formatter);
}

void Factory::registerAppender(std::shared_ptr<Appender> appender)
{
	assert(appender);

	std::lock_guard lock(_mutex);
	_appenders.push_back(appender);
	configure();
}

std::shared_ptr<Logger> Factory::getLogger(const std::string& name)
{
	std::lock_guard lock(_mutex);
	std::shared_ptr<Logger> l;

	char* tmp = new char[name.length() + 1];
	strcpy(tmp, name.c_str());
	auto node = _loggersTree.findNodeEnd(tmp);
	delete[] tmp;
	if (node)
	{
		l = node->_value;
	}

	if (!l)
	{
		l = std::make_shared<Logger>(name);
		l->setLogLevel(_config->getLogLevel(l.get(), NULL));
		_loggers.push_back(l);

		char* tmp = new char[name.length() + 1];
		strcpy(tmp, name.c_str());
		_loggersTree.insert(tmp, l);
		delete[] tmp;

		configure();
	}
	return l;
}

std::list<std::shared_ptr<Logger>> Factory::getLoggers() const
{
	std::lock_guard lock(_mutex);
	return _loggers;
}

std::string Factory::getVersion() const
{
	return std::string(HL_VERSION);
}

void Factory::configure()
{
	assert(_config);

	for (auto i = _loggers.begin(); i != _loggers.end(); ++i)
	{
		const auto logger = *i;

		// Setup log-level for `logger`.
		const int level = _config->getLogLevel(logger.get(), NULL);
		logger->setLogLevel(level);

		// Setup appenders for `logger`.
		for (auto a = _appenders.begin(); a != _appenders.end(); ++a)
		{
			const auto appender = *a;
			appender->setFormatter(_defaultFormatter->clone());

			// Add Appender to logger.
			if (!logger->hasAppender(appender))
			{
				logger->addAppender(appender);
			}
		}
	}
}

HL_NAMESPACE_END