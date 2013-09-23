cmake_minimum_required(VERSION 2.8)
project(humble_logging_library)

set(sources
  src/appender.cpp
  src/factory.cpp
  src/logger.cpp
  src/loglevel.cpp
  src/mutex_windows.cpp
)

if(WIN32)
  add_definitions(/Zc:wchar_t-)
  add_definitions(/INCREMENTAL:NO)
  add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif(WIN32)

include_directories(include)

add_library(humblelogginglib STATIC ${sources})

# Examples
add_subdirectory(examples/basic)
if(WIN32)
  add_subdirectory(examples/threaded)
endif(WIN32)
