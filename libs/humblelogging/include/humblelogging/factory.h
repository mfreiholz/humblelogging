#ifndef HL_FACTORY_H
#define HL_FACTORY_H

#include "humblelogging/defines.h"
#include "humblelogging/util/ternarytree.h"
#include <list>
#include <memory>
#include <mutex>
#include <string>

HL_NAMESPACE_BEGIN

class Logger;
class Appender;
class Formatter;
class Configuration;

/*!
	\class Factory
	\brief Main class to manage logging.

	Factory class is completely thread-safe and can be called from anywhere at anytime.
*/
class HUMBLE_EXPORT_API Factory final
{
private:
	Factory();

public:
	Factory(const Factory&) = delete;
	Factory& operator=(const Factory&) = delete;
	~Factory();

	/*!
		Gets the singleton instance of this Factory class.
	*/
	static Factory& getInstance();

	/*
		Sets the new Configuration and takes ownership of it.
		Deletes the previously used configuration.

		\param[in] config
			The new configuration to use.
			Note: It's not valid to pass a NULL pointer!

		\return Reference to the Factory itself.
	*/
	void setConfiguration(std::unique_ptr<Configuration> config);

	/*
		Sets the default formatter instance to be used by Appenders,
		which does not provide it's own Formatter.

		Changing the default Formatter will delete the previously instance.

		\param[in] formatter
			The Formatter instance to be used as default.

		\return Reference to the Factory itself.
	*/
	void setDefaultFormatter(std::unique_ptr<Formatter> formatter);

	/*
		Registers a new Appender object and takes ownership of it.

		\param[in] appender
			The new Appender to make available for all Loggers.
			Factory takes ownership of the Appender.

		\return Reference to the Factory itself.
	*/
	void registerAppender(std::shared_ptr<Appender> appender);

	/*
		Gets an existing or creates a new Logger object.

		\param[in] name
			The name of the logger. If no Logger with the name exists,
			the method will create a new one automatically.
			Note: The name is case sensitive.

		\return Reference to the existing or just created Logger instance.
	*/
	std::shared_ptr<Logger> getLogger(const std::string& name);

	/*!
		Gets a list with all existing loggers.
		
		\return List with all loggers.
	*/
	std::list<std::shared_ptr<Logger>> getLoggers() const;

	/*!
	*/
	std::string getVersion() const;

private:
	/*
		Runs the reconfiguration of all known Loggers and registered Appenders.

		\pre _mutex.lock()
	*/
	void configure();

private:
	mutable std::mutex _mutex;
	std::unique_ptr<Configuration> _config;
	std::unique_ptr<Formatter> _defaultFormatter;

	std::list<std::shared_ptr<Logger>> _loggers;
	TernaryTree<std::shared_ptr<Logger>> _loggersTree;
	std::list<std::shared_ptr<Appender>> _appenders;
};

HL_NAMESPACE_END
#endif