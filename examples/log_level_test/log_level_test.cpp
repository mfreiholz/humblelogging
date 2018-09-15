#include "humblelogging/api.h"

HUMBLE_LOGGER(L1, "leonardo");
HUMBLE_LOGGER(L2, "ams.sensor.s1");
HUMBLE_LOGGER(L3, "ams");

using namespace humble::logging;

int main(int argc, char** argv)
{
	(void)argc;
	(void)argv;
	Factory& fac = Factory::getInstance();
	fac.setConfiguration(DefaultConfiguration::createFromString(
		"logger.level(*)=info\n"
		//"logger.level(ams)=info\n"
		"logger.level(libmission*)=info\n"
		"logger.level(leonardo.picosar)=fatal\n"
		"logger.level(ams.sensor*)=fatal\n"
		"logger.level(ams.s2s.sync)=debug\n"));

	// Add appender as logging output.
	fac.registerAppender(new ConsoleAppender());

	// Do some test logs.
	HL_FATAL(L1, "TEST L1");
	HL_FATAL(L2, "TEST L2");
	HL_FATAL(L3, "TEST L3");

	return 0;
}
