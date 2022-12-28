#include "humblelogging/api.h"
using namespace humble::logging;

HUMBLE_LOGGER(logger, "default");

int main(int argc, char** argv)
{
	(void)argc;
	(void)argv;

	// Initialize some default settings.
	// Logs everything by default.
	Factory& fac = Factory::getInstance();

	// Optional: Change global log level for all Loggers.
	fac.setConfiguration(new SimpleConfiguration(LogLevel::All));

	// Add appender as logging output.
	fac.registerAppender(new ConsoleAppender());

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