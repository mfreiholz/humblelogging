cmake_minimum_required(VERSION 2.8)
project(HumbleLogging)
set(VERSION_MAJOR 1)
set(VERSION_MINOR 0)

option(BuildShared "BuildShared" ON)

if(BuildShared)
  set(StaticOrShared "SHARED")
  add_definitions(-DHUMBLE_LOGGING_EXPORT)
else(BuildShared)
  set(StaticOrShared "STATIC")
endif(BuildShared)

if(CMAKE_COMPILER_IS_GNUCXX)
  set(CMAKE_CXX_FLAGS "-std=c++11")
endif(CMAKE_COMPILER_IS_GNUCXX)

set(headers
  include/humblelogging/api.h
  include/humblelogging/appender.h
  include/humblelogging/defines.h
  include/humblelogging/factory.h
  include/humblelogging/formatter.h
  include/humblelogging/logevent.h
  include/humblelogging/logger.h
  include/humblelogging/loglevel.h
  include/humblelogging/mutex.h
)

set(sources
  src/appender.cpp
  src/factory.cpp
  src/formatter.cpp
  src/logevent.cpp
  src/logger.cpp
  src/loglevel.cpp
)

if(WIN32)
  add_definitions(/Zc:wchar_t-)
  add_definitions(/INCREMENTAL:NO)
  add_definitions(-D_CRT_SECURE_NO_WARNINGS)
  list(APPEND headers include/humblelogging/mutex_windows.h)
  list(APPEND sources src/mutex_windows.cpp)
endif(WIN32)

include_directories(include)

# Target
add_library(humblelogging ${StaticOrShared} ${sources})

# Install
install(TARGETS humblelogging
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
)
install(FILES ${headers} DESTINATION include/humblelogging)
install(FILES cmake/FindHumbleLogging.cmake DESTINATION cmake)

# Examples
add_subdirectory(examples/basic)
if(WIN32)
  add_subdirectory(examples/threaded)
endif(WIN32)
