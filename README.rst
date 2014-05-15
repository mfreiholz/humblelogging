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
