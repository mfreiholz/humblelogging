# Tutorial

This tutorial provides you with a quick introduction to HumbleLogging.
Note that this tutorial is always based on the latest release version.
Please also check out the examples that are shipped with the
sources.

## Creating a test project <a class="anchor" name="create-a-test-project"></a>

You can start the initialization at any place in your code,
but it is recommended to initialize logging within your `main()`
function or bootstrap code at the very beginning of your application.

```cpp
// simple_logging.cpp
#include "humblelogging/api.h"

HUMBLE_LOGGER(logger, "default");

using namespace humble::logging;

int main(int argc, char **argv)
{
  (void) argc;
  (void) argv;

  // Initialize some default settings.
  // Logs everything by default.
  Factory &fac = Factory::getInstance();

  // Optional: Change global log level for all Loggers.
  fac.setConfiguration(new SimpleConfiguration(LogLevel::All));

  // Add appender as logging output.
  fac.registerAppender(new ConsoleAppender());

  // Do some test logs.
  HL_TRACE(logger, "Trace log");
  HL_DEBUG(logger, "Debug log");
  HL_INFO (logger, "Info log");
  HL_WARN (logger, "Warn log");
  HL_ERROR(logger, "Error log");
  HL_FATAL(logger, "Fatal log");

  return 0;
}
```

By including `humblelogging/humblelogging.h` you get all the required headers
and macros you need to log within your current source file.

The `HUMBLE_LOGGER` macro creates a new or retrieves an already existing
Logger object by its name and prepares it to be used in the current
source file. You can create as many Loggers as you want, as long as you
use a different local variable name for it, which is provided by
first parameter => `HUMBLE_LOGGER(variableName, loggerName)`

```cpp
// Multiple loggers
HUMBLE_LOGGER(commonLogger,      "default");
HUMBLE_LOGGER(performanceLogger, "performance");
HUMBLE_LOGGER(networkLogger,     "network.tcp");
```

The Loggers do not log anything until an `Appender` has been registered.
You can register one or more Appenders with the
`Factory::registerAppender()` function. HumbleLogging does have the most
important Appenders built-in.

```cpp
// Registering multiple appenders.
fac.registerAppender(new humble::logging::ConsoleAppender());
fac.registerAppender(new humble::logging::FileAppender("simple.log", false));
fac.registerAppender(new humble::logging::RollingFileAppender("rolling.log", false, 5, 1024L * 1024L));
```

Please read the header files, found in *include/humblelogging/appender*
for further documentation about the parameters.

As a last initialization step you need to define up to which log level
you want to track log-events. You can change the log level with the
`Factory.setConfiguration(...)` method.

```cpp
// Change the global log-level.
auto &fac = humble::logging::Factory::getInstance();
fac.setConfiguration(new humble::logging::SimpleConfiguration(LogLevel::All));
```

By using the predefined macros `HL_TRACE`, `HL_DEBUG`, `HL_INFO`,
`HL_WARN`, `HL_ERROR` and `HL_FATAL` your are able to log within your
source code in different log-levels.

Well, that's basically all you need to add simple logging functionality
to your project.


## Configure by file <a class="anchor" name="configure-by-file"></a>

Configurations are used to initialize log-levels for your Loggers.
HumbleLogging provides a `DefaultConfiguration` implementation which
provides functionality to parse a file or string with a special syntax.

```cpp
// Load configuration from file.
auto &fac = humble::logging::Factory::getInstance();
fac.setConfiguration(humble::logging::DefaultConfiguration::createFromFile("/path/to/logging.conf"));
```

### The config file

The example configuration shows that it is not required to rely on a
specific pattern of Logger names. The framework is based on simple
string and prefix searches. If it is required to specify a log-level
recursive, the wildcard (*) can be used.

```
# Sets the default log-level to OFF.
logger.level(*)=off

# Specify a specific log-level for a few loggers.
logger.level(core*)=fatal
logger.level(core.network*)=error
logger.level(core.network.tcp*)=debug

# Some more loggers with different names.
logger.level(Core*)=fatal
logger.level(CoreNetwork*)=error
logger.level(Audio*)=warn
logger.level(Video*)=warn
logger.level(VideoCapture*)=off
```

## Using custom log output format <a class="anchor" name="using-custom-log-output-format"></a>

Formatters are used to give your log output a special format.
HumbleLogging uses the built-in `SimpleFormatter` which has a fixed
predefined format as default. However, the library also comes with a
`PatternFormatter` which allows you to define your custom log message
format very easily.

```cpp
// Use custom log message format.
auto &fac = humble::logging::Factory::getInstance();
fac.setDefaultFormatter(new PatternFormatter("%date - %lls -> %m"));
```
