#include "humble-logging.h"

HUMBLE_LOGGER(logger, "default");

using namespace humble::logging;

int main(int argc, char **argv)
{
  HL_DEBUG(logger, "Initialize logging (this text should NOT be logged).");

  Factory &fac = Factory::getInstance();
  fac.registerAppender(new ConsoleAppender());
  fac.registerAppender(new FileAppender("humble.log"));
  fac.configure();

  HL_DEBUG(logger, "Begin of example.");

  for (int i = 0; i < 10; ++i) {
    HL_TRACE(logger, std::string("Iteration ") + std::string(" of 10"));
  }

  HL_DEBUG(logger, "End of example.");
  return 0;
}
