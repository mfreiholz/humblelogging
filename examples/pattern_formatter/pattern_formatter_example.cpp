#include "humblelogging/api.h"

HUMBLE_LOGGER(logger, "default");

using namespace humble::logging;

int main(int argc, char** argv)
{
	(void)argc;
	(void)argv;

	// Initialize some default settings.
	// Logs everything by default.
	Factory& fac = Factory::getInstance();

	// Optional: Change global log level for all Loggers.
	fac.setConfiguration(new SimpleConfiguration(LogLevel::All));

	// Optional: Change default formatter.
	fac.setDefaultFormatter(new PatternFormatter("%date\t%lls\t%name\t%filename:%line\t%m\n"));

	// Add appender as logging output.
	fac.registerAppender(new ConsoleAppender());

	// Do some test logs.
	HL_TRACE(logger, "Trace log");
	HL_DEBUG(logger, "Debug log");
	HL_INFO(logger, "Info log");
	HL_WARN(logger, "Warn log");
	HL_ERROR(logger, "Error log");
	HL_FATAL(logger, "Fatal log");

	return 0;
}