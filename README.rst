Humble Logging Library (C++)
============================
:Version:
  Still in development.


How To Build
============
Thanks to CMake and the no dependency term, the project build is very easy.
::

  cd $PROJECT_DIRECTORY
  mkdir build
  cd build
  cmake -DCMAKE_INSTALL_PREFIX:PATH=/home/libs/humblelogging ..
  
After you ran these commands you should have a `Makefile` or Visual Studio solution `*.sln` to build the library.
The "install" target will copy all public headers, libraries and cmake scripts into the ``CMAKE_INSTALL_PREFIX`` directory.


Build Options
-------------
cmake -DBuildShared=OFF
  Builds the library as static or shared library (default=ON).
  

Use the library
---------------
Set the environment variable ``HumbleLogging_DIR`` to the directory, which has been used as ``CMAKE_INSTALL_PREFIX`` in the build step.
::

  HumbleLogging_DIR=/home/libs/humblelogging
  export HumbleLogging_DIR

Now the included ``FindHumbleLoggingLibrary.cmake`` script can be used. Append this to your ``CMakeLists.txt``:
__TODO(mfreiholz)__ Add cmake.config script which makes this step obsolete!
::

  # Add find script path.
  set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};$ENV{HumbleLogging_DIR}/cmake")
  
  # Add dependency.
  find_package(HumbleLogging)
  include_directories(${HUMBLE_LOGGING_INCLUDE_DIRS})
  
  # Link library against your executable.
  add_executable(test_exe ${sources})
  target_link_libraries(test_exe ${HUMBLE_LOGGING_LIBRARIES})
