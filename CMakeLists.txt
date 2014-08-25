cmake_minimum_required(VERSION 2.8)
project(HumbleLogging)
set(VERSION_MAJOR 1)
set(VERSION_MINOR 0)

option(BuildShared "BuildShared" ON)
option(BuildExamples "BuildExamples" ON)
option(BuildLockFree "BuildLockFree" OFF)
option(IncludeFunctionSignature "IncludeFunctionSignature" OFF)

if(BuildShared)
  set(StaticOrShared "SHARED")
  add_definitions(-DHUMBLE_LOGGING_EXPORT)
else(BuildShared)
  set(StaticOrShared "STATIC")
endif(BuildShared)

if(CMAKE_COMPILER_IS_GNUCXX)
  set(CMAKE_CXX_FLAGS "-std=c++11")
endif(CMAKE_COMPILER_IS_GNUCXX)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)

# Sources
set(headers
  include/humblelogging/util/mutex.h
  include/humblelogging/util/spinlock.h
  include/humblelogging/util/patternconfigregistry.h
  include/humblelogging/util/processinfo.h
  include/humblelogging/util/ternarytree.h
  include/humblelogging/api.h
  include/humblelogging/appender.h
  include/humblelogging/configuration.h
  include/humblelogging/defines.h
  include/humblelogging/factory.h
  include/humblelogging/formatter.h
  include/humblelogging/logevent.h
  include/humblelogging/logger.h
  include/humblelogging/loglevel.h
)

set(sources
  src/util/patternconfigregistry.cpp
  src/util/processinfo.cpp
  src/appender.cpp
  src/configuration.cpp
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
  if(NOT BuildLockFree)
    list(APPEND headers include/humblelogging/util/mutex_windows.h)
    list(APPEND headers include/humblelogging/util/spinlock_windows.h)
    list(APPEND sources src/util/mutex_windows.cpp)
    list(APPEND sources src/util/spinlock_windows.cpp)
  endif()
else(WIN32)
  if(NOT BuildLockFree)
    list(APPEND headers include/humblelogging/util/mutex_linux.h)
    list(APPEND headers include/humblelogging/util/spinlock_linux.h)
    list(APPEND sources src/util/mutex_linux.cpp)
    list(APPEND sources src/util/spinlock_linux.cpp)
  endif()
endif(WIN32)

if(BuildLockFree)
  list(APPEND headers include/humblelogging/util/mutex_nolock.h)
  list(APPEND headers include/humblelogging/util/spinlock_nolock.h)
  list(APPEND sources src/util/mutex_nolock.cpp)
  list(APPEND sources src/util/spinlock_nolock.cpp)
endif(BuildLockFree)

if(IncludeFunctionSignature)
  add_definitions(-DHUMBLE_INCLUDE_PRETTY_FUNCTION)
endif(IncludeFunctionSignature)

include_directories(include)

# Target
add_library(humblelogging ${StaticOrShared} ${sources} ${headers})

# Install
install(TARGETS humblelogging
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
)
install(FILES ${headers} DESTINATION include/humblelogging)
install(FILES cmake/FindHumbleLogging.cmake DESTINATION cmake)

# Examples
if(BuildExamples)
  add_subdirectory(examples/basic)
  add_subdirectory(examples/configured)
  add_subdirectory(examples/performance)
  add_subdirectory(examples/mtperformance)
  if(WIN32)
    add_subdirectory(examples/threaded)
  endif(WIN32)
endif(BuildExamples)
