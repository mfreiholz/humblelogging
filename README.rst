Humble Logging Library (C++)
============================
Lightweight C++ Logging Library


Dependencies
============
Except the STL (Standard Template Library), which should be on nearly every system,
the project doesn't require third-party libraries.

Note: Linux requires ``std::mutex``


How To Build
============
Type on your console
::

  cd $PROJECT_DIRECTORY
  mkdir build
  cd build
  cmake -DCMAKE_INSTALL_PREFIX:PATH=/tmp/humblelogging ..
  
After you ran these commands you should have a ``Makefile`` or Visual Studio solution ``*.sln`` to build the library.
The ``install`` target will copy all public headers, libraries and cmake scripts into the ``CMAKE_INSTALL_PREFIX`` directory.


Build Options
-------------
cmake -DBuildShared=OFF
  Builds the library as static or shared library.
  ``default=ON``
  
cmake -DBuildExamples=OFF
  Builds all sub projects in the ``./examples/`` folder.
  ``default=ON``


Examples
--------
See the ``./examples/basic/`` folder for an short introduction.


Example configuration file
--------------------------
The example configuration shows, that it is not required to rely on a specific pattern of Logger names.
The framework is based on simple strings and prefix searches. If it is required to specify a log-level recursive
the wildcard (*) have to be used.
::

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


Build Compatibility
-------------------
The project build has been tested in the following environments.
* Windows 8.1 Update 1 Visual Studio 2008 (32 & 64 bit)
* Windows 8.1 Update 1 Visual Studio 2010 (32 & 64 bit)
* Windows 8.1 Update 1 Visual Studio 2012 (32 & 64 bit)
* Ubuntu 14.04 GCC 4.8 (32 & 64 bit)
