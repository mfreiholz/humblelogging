Humble Logging Library (C++)
============================
Lightweight C++ Logging Library


How To Build
============
Thanks to CMake and the no dependency term of the project, building is very easy.
::

  cd $PROJECT_DIRECTORY
  mkdir build
  cd build
  cmake -DCMAKE_INSTALL_PREFIX:PATH=/home/libs/humblelogging ..
  
After you ran these commands you should have a ``Makefile`` or Visual Studio solution ``*.sln`` to build the library.
The ``install`` target will copy all public headers, libraries and cmake scripts into the ``CMAKE_INSTALL_PREFIX`` directory.


Build Options
-------------
cmake -DBuildShared=OFF
  Builds the library as static or shared library.
  ``default=ON``


Examples
--------
See the ``examples\basic`` folder for an short introduction.
