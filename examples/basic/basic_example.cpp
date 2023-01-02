#include "humblelogging/humblelogging.h"

HUMBLE_LOGGER(logger, "default");

static void init_logging()
{
	using namespace humble::logging;

	// Initialize some default settings.
	// Logs everything by default.
	Factory& fac = Factory::getInstance();

	// Method #1: Setup with fixed log level.
	fac.setConfiguration(std::make_unique<Configuration>(LogLevel::All));

	// Method #2: Setup from config file format.
	auto config = std::make_unique<Configuration>();
	config->loadFromString(
		"logger.level(*)=fatal\n"
		"logger.level(core*)=error\n"
		"logger.level(core.local*)=warn\n"
		"logger.level(core.network*)=info\n"
		"logger.level(core.network.tcp*)=debug\n"
		"logger.level(core.network.udp.datagram)=trace\n");
	fac.setConfiguration(std::move(config));

	// Register Appender as logging output.
	fac.registerAppender(std::make_shared<ConsoleAppender>());
}

int main(int, char**)
{
	init_logging();

	// Do some test logs.
	HL_TRACE(logger, "Trace log");
	HL_DEBUG(logger, "Debug log");
	HL_INFO(logger, "Info log");
	HL_WARN(logger, "Warn log");
	HL_ERROR(logger, "Error log");
	HL_FATAL(logger, "Fatal log");

	// Logging with `printf()` style.
	HL_FATAL_F(logger, "Log with %s", "HL_FATAL_F");
	HL_ERROR_F(logger, "Log with %s", "HL_ERROR_F");
	HL_INFO_F(logger, "Log with %s", "HL_INFO_F");
	HL_DEBUG_F(logger, "Log with %s", "HL_DEBUG_F");
	HL_TRACE_F(logger, "Log with %s", "HL_TRACE_F");
	HL_TRACE_F(logger, "Log with <no parameters>");

	return 0;
}