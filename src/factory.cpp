#include "humblelogging/factory.h"
#include "humblelogging/appender.h"
#include "humblelogging/configuration.h"
#include "humblelogging/configuration/simpleconfiguration.h"
#include "humblelogging/formatter.h"
#include "humblelogging/formatter/simpleformatter.h"
#include "humblelogging/logger.h"
#include "humblelogging/loglevel.h"
#include <algorithm>
#include <cstring>
#include <list>
#include <string>

HL_NAMESPACE_BEGIN

Factory::Factory()
	: _config(new SimpleConfiguration(LogLevel::All))
	, _defaultFormatter(new SimpleFormatter())
{
}

Factory::~Factory()
{
	MutexLockGuard lock(_mutex);
	while (!_loggers.empty())
	{
		Logger* l = _loggers.front();
		_loggers.pop_front();
		delete l;
	}
	while (!_appenders.empty())
	{
		Appender* a = _appenders.front();
		_appenders.pop_front();
		delete a;
	}
	if (_defaultFormatter)
	{
		delete _defaultFormatter;
		_defaultFormatter = NULL;
	}
	if (_config)
	{
		delete _config;
		_config = NULL;
	}
}

Factory& Factory::getInstance()
{
	static Factory _instance;
	return _instance;
}

Factory& Factory::setConfiguration(Configuration* config)
{
	MutexLockGuard lock(_mutex);
	if (_config && config != _config)
	{
		delete _config;
		_config = NULL;
	}
	_config = config;
	configure();
	return *this;
}

Factory& Factory::registerAppender(Appender* appender)
{
	MutexLockGuard lock(_mutex);
	_appenders.push_back(appender);
	configure();
	return *this;
}

Logger& Factory::getLogger(const std::string& name)
{
	MutexLockGuard lock(_mutex);
	Logger* l = 0;

	char* tmp = new char[name.length() + 1];
	strcpy(tmp, name.c_str());
	TernaryNode<Logger*>* node = _loggersTree.findNodeEnd(tmp);
	delete[] tmp;
	if (node)
	{
		l = node->_value;
	}

	if (l == 0)
	{
		l = new Logger(name);
		l->setLogLevel(_config->getLogLevel(l, NULL));
		_loggers.push_back(l);

		char* tmp = new char[name.length() + 1];
		strcpy(tmp, name.c_str());
		_loggersTree.insert(tmp, l);
		delete[] tmp;

		configure();
	}
	return (*l);
}

Factory& Factory::setDefaultFormatter(Formatter* formatter)
{
	if (!formatter)
	{
		return *this;
	}
	MutexLockGuard lock(_mutex);
	if (_defaultFormatter)
	{
		delete _defaultFormatter;
	}
	_defaultFormatter = formatter;
	return *this;
}

Formatter* Factory::getDefaultFormatter() const
{
	MutexLockGuard lock(_mutex);
	return _defaultFormatter;
}

void Factory::configure()
{
	for (std::list<Logger*>::iterator i = _loggers.begin(); i != _loggers.end(); ++i)
	{
		Logger* logger = *i;

		// Get LogLevel from config for Logger.
		if (_config)
		{
			const int level = _config->getLogLevel(logger, NULL);
			logger->setLogLevel(level);
		}

		for (std::list<Appender*>::iterator a = _appenders.begin(); a != _appenders.end(); ++a)
		{
			Appender* appender = *a;
			if (!appender->getFormatter())
			{
				appender->setFormatter(_defaultFormatter->copy());
			}

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
