# Find "include" directory of installation.
find_path(HLL_INCLUDE_DIR
  humblelogging/api.h
  HINTS ../include
)

# Windows libs.
if(WIN32)
  find_library(HLL_LIBRARY
    NAMES humblelogging
    HINTS ../lib
  )
endif(WIN32)

# Linux libs.
if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
  find_library(HLL_LIBRARY
    NAMES libhumblelogging.a libhumblelogging.so
    HINTS $ENV{HumbleLogging_DIR}/lib
  )
endif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")

# Export variables.
set(HumbleLogging_FOUND)
set(HumbleLogging_INCLUDE_DIRS ${HLL_INCLUDE_DIR})
set(HumbleLogging_LIBRARIES optimized ${HLL_LIBRARY} debug ${HLL_LIBRARY})
set(HumbleLogging_DEFINITIONS)