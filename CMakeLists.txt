cmake_minimum_required(VERSION 2.8)
project(humble_logging_library)

set(sources
  src/appender.cpp
  src/factory.cpp
  src/logger.cpp
  src/loglevel.cpp
)

if(WIN32)
  add_definitions(/Zc:wchar_t-)
  add_definitions(/INCREMENTAL:NO)
endif(WIN32)

include_directories(include)

add_library(humblelogginglib STATIC ${sources})

# Examples
add_subdirectory(examples/basic)
