Humble Logging Library (C++)
============================
:Initiator:
  Manuel Freiholz <http://thehumbleguy.de/>
:Contributors:
  None.
:Version:
  Still in development.


How To Build
============
::

  cd $PROJECT_DIRECTORY
  mkdir build
  cd build
  cmake -DCMAKE_INSTALL_PREFIX:PATH=/home/libs/humblelogging ..
  
After you have run these commands you should have a `Makefile` or Visual Studio solution to build the library.
The "install" target will copy all public headers, libraries and cmake scripts into the `CMAKE_INSTALL_PREFIX` directory.


Build Options
-------------
cmake -DBuildShared=ON
  Builds the library as shared \*.dll on Windows.
  

Use the library
---------------
Set the environment variable `HUMBLE_LOGGING_DIR` to the directory, which has been used as `CMAKE_INSTALL_PREFIX`.
::

  HUMBLE_LOGGING_DIR=/home/libs/humblelogging
  export HUMBLE_LOGGING_DIR

Now the included `FindHumbleLoggingLibrary.cmake` script can be used. Append this to your `CMakeLists.txt`:
::

  # Add find script path.
  set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};$ENV{HUMBLE_LOGGING_DIR}/cmake")
  
  # Add dependency.
  find_package(HumbleLoggingLibrary)
  include_directories(${HUMBLE_LOGGING_INCLUDE_DIRS})
  
  # Link library against your executable.
  add_executable(test_exe ${sources})
  target_link_libraries(test_exe ${HUMBLE_LOGGING_LIBRARIES})
