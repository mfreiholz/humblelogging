# HumbleLogging Framework (C++)

<img src="https://raw.githubusercontent.com/mfreiholz/humblelogging/master/logo.png" title="HumbleLogging" style="float: right;">

HumbleLogging is a lightweight C++ logging framework.  
It aims to be extendible, easy to understand and as fast as possible.

[![Build Status](https://api.travis-ci.org/mfreiholz/humblelogging.svg?branch=master)](https://travis-ci.org/mfreiholz/humblelogging)


# Documentation

- [Features](#)
	- [Built-in Appenders](#)
	- [Built-in Formatters](#)
- [Build & Installation](#)
	- [Build from source](#)
	- [Build options](#)
- [Tutorial](#)
	- [Creating a test project](#)
	- [Configure by file](#)
	- [Using custom log output format](#)
- [Benchmarks](#)
	- [Submit your benchmark](#)
	- [Existing benchmarks](#)
- [Download](#)
- [Feedback & Contribute](#)


# Features

- Portable logging library for >= C++98
- Dependency free, no third-party libraries required
- Synchronized logging accross multiple threads
- Configuration from external file
- Changeable log-levels, appenders (outputs) and formats during runtime
- No restriction on logger names
- Multiple appenders for loggers (outputs)
- Simple API to implement custom appenders and formatters
- Custom format for log messages

## Built-in Appenders

- **NullAppender**  
  Doesn't log anything. It is mostly used for performance testing.

- **ConsoleAppender**  
  Prints log-events to `stdout`.  
  *Upcoming:* Additionally logs to Visual Studio's application output
  window.

- **FileAppender**  
  Writes all log-events to a single file.

- **RollingFileAppender**  
  Writes all log-events to a file which gets rolled as it reaches
  a configured size (e.g.: file.log, file.log.1, file.log.2, ...).
  The file's size and the number of files can be configured.

## Built-in Formatters

- **SimpleFormatter**  
  The default Formatter includes the most important information in a
  predefined layout.

- **PatternFormatter**  
  Provides placeholders to define a custom log messages format  
  (e.g.: `[%date] [%lls] [line=%line] [file=%filename] %m\n`)


# Build & Installation

## Prerequisites

HumbleLogging only needs a C++98 or C++11 compiler and an available
implementation of the standard template library (STL). HumbleLogging has
been successfully compiled with g++ (>=4.7) and Visual C++ (>=2008).
It has been tested on Linux and Microsoft Windows.

## Build from source

Download the latest release package (*.tar* or *.zip*),
unpack the compressed archive and enter the directory.

```bash
tar -xfz humblelogging-XXX.tar.gz
cd humblelogging
```

Building from source requires [CMake][cmake-homepage] (>=2.8)
installed on your machine.

```bash
mkdir build
cd build
cmake ..
```

After you ran these commands you have a *Makefile* or
Visual Studio solution (*.sln*) to build the library.

*Linux:* Type `make` as next command in your console to build.

*Windows:* Double click the `HumbleLogging.sln` and build with
Visual Studio.

## Build options

HumbleLogging can be build in different variants which makes it
possible to run in many different environments with best settings.
All build-options must be provided as CMake command line arguments with
the `-D` parameter. You can append as many options as you want.

**-DBuildShared=OFF** `default=ON`
> Builds the library as static or shared library.

**-DBuildExamples=ON** `default=OFF`
> Builds all sub projects in the `./examples/` folder.
> You do not need these projects to include the library in your project,
> but they might be used for testing purposes.

**-DBuildLockFree=ON** `default=OFF`
> Builds the library in lock-free mode.
> Mutexes and SpinLocks classes doesn't block execution and do no
> synchronization at all.
> Improves the performance in environments where only one thread is
> running.
>
> This option makes the library C++98 compatible.
>
> Do not use in combination with `-DBuildSystemNative=ON`

**-DBuildSystemNative=ON** `default=off`
> Builds the library with system-native implementations instead of using
> the C++11 STL provided classes.
>
> This options makes the library C++98 compatible.
>
> Do not use in combination with `-DBuildLockFree=ON`
>
> **Linux** requires `pthread` for its mutex implementation.

**-DIncludeFunctionSignature=ON** `default=OFF`
> Enabling this features will add the function signature of the current
> stack to the LogEvent. Using this features does decrease performance.
>
> **Note:** It's redundant information since each log-event already
> contains the file's name and line number.


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

# Benchmarks

## Submit your benchmark

You can commit your own benchmark with a pull-request on GitHub for this file.

## Existing benchmarks

All benchmarks are created with the *mtperformance_example* binary
which is shipped as an example project with HumbleLogging source.

```
Usage:
  binary [thread-count] [events-per-thread] [appender]
```

The result gets more accurate by increasing the number of log-events.
You should use a minimum of 20000000 log-events per thread to get a good
result. The benchmarks on this page always use the *null* appender.
The number of threads should equal the number of real-cores of your
machine (no Hyperthreading cores).
E.g:

```bash
mtperformance_example.exe 4 20000000 null
```

### Current master branch

Environment | Events | Threads | Duration (ms) | Throughput (events/second)
------------|--------|---------|---------------|---------------------------
Windows 8.1 Update 2 32 bit / VC 2013 Community / Core i7 3770K @ 3.50 GHz | 80000000 | 4 | 10619 | 7533666

### Release 1.0

Environment | Events | Threads | Duration (ms) | Throughput (events/second)
------------|--------|---------|---------------|---------------------------
Windows 8.1 Update 1 32 bit / VC 2012 / Core i7 3770K @ 3.50 GHz | 80000000 | 4 | 12468 | 6416426
Windows 8.1 Update 2 32 bit / VC 2013 Community / Core i7 920 @ 2.67 GHz | 80000000 | 4 | 18645 | 4290695
Windows 8.1 Update 2 64 bit / VC 2013 Community / Core i7 920 @ 2.67 GHz | 80000000 | 4 | 15320 | 5221932


# Contribute & Feedback

HumbleLogging is developed by Manuel Freiholz from Germany.
Contact Manuel on his social media accounts ([Facebook][fb],
[Twitter][tw]) for any questions, comments or whether you'd like to
contribute.

Feel free to write a review, comparison, benchmark or
[submit bugs and features][github-issues] on GitHub.

## Contributors

Daniel Toplak, Germany, [GitHub Profile](https://github.com/hsimpson)


[cmake-homepage]: https://www.cmake.org/
[fb]: https://www.facebook.com/manuel.freiholz
[tw]: https://twitter.com/mfreiholz
[github-issues]: https://github.com/mfreiholz/humblelogging/issues