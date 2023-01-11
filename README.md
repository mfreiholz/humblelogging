# HumbleLogging Framework (C++)

<img src="https://raw.githubusercontent.com/mfreiholz/humblelogging/master/logo.png" title="HumbleLogging" style="float: right;">

HumbleLogging is a lightweight C++ logging framework.  
It aims to be extendible, easy to understand and as fast as possible.

[![Build Status](https://api.travis-ci.org/mfreiholz/humblelogging.svg?branch=master)](https://travis-ci.org/mfreiholz/humblelogging)

__Do NOT use `master` branch for productivity!__

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

- Portable logging library (C++17)
- Dependency free, no third-party libraries required
- Synchronized logging accross multiple threads
- Configuration from external file
- Changable log-levels, appenders (outputs) and formats during runtime
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

HumbleLogging only needs a _C++98 (Limited)_ or C++11 compiler and an available
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

**-DBuildShared=ON** `default=OFF`
> Builds the library as static or shared library.

**-DBuildTests=ON** `default=OFF`
> Builds all sub projects in the `./tests/` folder, based on GTest.
> You do not need these projects to include the library in your project,
> but they might be used for testing purposes.

**-DBuildApps=OFF** `default=ON`
> Builds all sub projects in the `./apps/` folder.
> You do not need these projects to include the library in your project,
> but they might be used for testing purposes.

# Usage

See `./apps/basic_example` for a working example.

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