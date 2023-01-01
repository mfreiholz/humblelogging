#include "humblelogging/factory.h"
#include "humblelogging/appender.h"
#include "humblelogging/configuration.h"
#include "humblelogging/formatter.h"
#include "humblelogging/formatter/simpleformatter.h"
#include "humblelogging/logger.h"
#include "humblelogging/loglevel.h"
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

Factory& Factory::setConfiguration(std::unique_ptr<Configuration> config)
{
	assert(config);

	std::lock_guard lock(_mutex);
	_config = std::move(config);
	configure();
	return *this;
}

Factory& Factory::setDefaultFormatter(std::unique_ptr<Formatter> formatter)
{
	assert(formatter);

	std::lock_guard lock(_mutex);
	_defaultFormatter = std::move(formatter);
	return *this;
}

Factory& Factory::registerAppender(std::shared_ptr<Appender> appender)
{
	assert(appender);

	std::lock_guard lock(_mutex);
	_appenders.push_back(appender);
	configure();
	return *this;
}

Logger& Factory::getLogger(const std::string& name)
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
	return (*l);
}

void Factory::configure()
{
	for (auto i = _loggers.begin(); i != _loggers.end(); ++i)
	{
		auto logger = *i;

		// Get LogLevel from config for Logger.
		if (_config)
		{
			const int level = _config->getLogLevel(logger.get(), NULL);
			logger->setLogLevel(level);
		}

		for (auto a = _appenders.begin(); a != _appenders.end(); ++a)
		{
			auto appender = *a;
			appender->setFormatter(_defaultFormatter->clone());

			// Add Appender to logger.
			if (!logger->hasAppender(appender))
			{
				logger->addAppender(appender);
			}

			// Get LogLevel from config, based on appender.
			// Note: Not yet supported!
			//if (_config) {
			//  const int level = _config->getLogLevel(logger, appender);
			//  appender->setLogLevel(level);
			//}
		}
	}
}

HL_NAMESPACE_END