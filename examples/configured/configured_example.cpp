#include "humblelogging/humblelogging.h"

HUMBLE_LOGGER(L0, "core");
HUMBLE_LOGGER(L1, "core.local");
HUMBLE_LOGGER(L2, "core.local.file");
HUMBLE_LOGGER(L3, "core.local.folder");
HUMBLE_LOGGER(L4, "core.network");
HUMBLE_LOGGER(L5, "core.network.tcp");
HUMBLE_LOGGER(L6, "core.network.udp.datagram");

using namespace humble::logging;

int main(int argc, char** argv)
{
	(void)argc;
	(void)argv;

	Factory& fac = Factory::getInstance();

	auto config = std::make_unique<Configuration>();
	config->loadFromString(
		"logger.level(*)=fatal\n"
		"logger.level(core*)=error\n"
		"logger.level(core.local*)=warn\n"
		"logger.level(core.network*)=info\n"
		"logger.level(core.network.tcp*)=debug\n"
		"logger.level(core.network.udp.datagram)=trace\n");
	fac.setConfiguration(std::move(config));
	fac.registerAppender(std::make_shared<ConsoleAppender>());

	// Every event should be logged.
	HL_FATAL(L0, "#0 Logging: core");
	HL_WARN(L1, "#1 Logging: core.local");
	HL_WARN(L2, "#2 Logging: core.local.file");
	HL_WARN(L3, "#3 Logging: core.local.folder");
	HL_INFO(L4, "#4 Logging: core.network");
	HL_DEBUG(L5, "#5 Logging: core.network.tcp");
	HL_TRACE(L6, "#6 Logging: core.network.udp.datagram");
	return 0;
}
