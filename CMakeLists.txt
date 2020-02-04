cmake_minimum_required(VERSION 2.8)
project(humblelogging)

set(VERSION_MAJOR 3)
set(VERSION_MINOR 0)
set(VERSION_PATCH 2)
set(VERSION_EXTRA "")

#
# Options
#

option(BuildShared "BuildShared" OFF)
option(BuildExamples "BuildExamples" OFF)
option(BuildLockFree "BuildLockFree" OFF)
option(BuildSystemNative "BuildSystemNative" OFF)
option(IncludeFunctionSignature "IncludeFunctionSignature" OFF)

if(BuildShared)
	set(StaticOrShared "SHARED")
	add_definitions(-DHUMBLELOGGING_EXPORT)
else(BuildShared)
	set(StaticOrShared "STATIC")
endif(BuildShared)

if(IncludeFunctionSignature)
	add_definitions(-DHUMBLE_INCLUDE_PRETTY_FUNCTION)
endif(IncludeFunctionSignature)

if(WIN32)
	add_definitions(/Zc:wchar_t-)
	add_definitions(/INCREMENTAL:NO)
	add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif(WIN32)

if(CMAKE_COMPILER_IS_GNUCXX)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")
endif(CMAKE_COMPILER_IS_GNUCXX)

#
# Sources
#

set(headers
	include/humblelogging/appender/consoleappender.h
	include/humblelogging/appender/fileappender.h
	include/humblelogging/appender/nullappender.h
	include/humblelogging/appender/rollingfileappender.h
	include/humblelogging/formatter/simpleformatter.h
	include/humblelogging/formatter/patternformatter.h
	include/humblelogging/configuration/defaultconfiguration.h
	include/humblelogging/configuration/simpleconfiguration.h
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
	include/humblelogging/humblelogging.h
	include/humblelogging/logevent.h
	include/humblelogging/logger.h
	include/humblelogging/loglevel.h
)

set(sources
	src/appender/consoleappender.cpp
	src/appender/fileappender.cpp
	src/appender/nullappender.cpp
	src/appender/rollingfileappender.cpp
	src/formatter/simpleformatter.cpp
	src/formatter/patternformatter.cpp
	src/configuration/defaultconfiguration.cpp
	src/configuration/simpleconfiguration.cpp
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

# Choose correct mutex implementation.
if(BuildLockFree)
	list(APPEND sources src/util/mutex_nolock.cpp)
	list(APPEND sources src/util/spinlock_nolock.cpp)
else()
	if(BuildSystemNative)
		if(WIN32)
			list(APPEND sources src/util/mutex_windows_native.cpp)
			list(APPEND sources src/util/spinlock_windows_native.cpp)
		endif()
		if(UNIX)
			list(APPEND sources src/util/mutex_linux_native.cpp)
			list(APPEND sources src/util/spinlock_linux_native.cpp)
		endif()
	else()
		if(UNIX)
			set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
		endif()
		list(APPEND sources src/util/mutex_c11.cpp)
		list(APPEND sources src/util/spinlock_c11.cpp)
	endif()
endif()

#source_group(
#	TREE ${CMAKE_CURRENT_SOURCE_DIR}
#	#PREFIX src
#	FILES ${headers} ${sources}
#)

#
# Includes
#

include_directories(include)

#
# Target
#

add_library(
	${PROJECT_NAME}
	${StaticOrShared}
	${sources}
	${headers}
)

if(BuildSystemNative)
	if(UNIX)
		target_link_libraries(${PROJECT_NAME} pthread)
	endif()
endif()

#
# Install
#

install(TARGETS humblelogging
	RUNTIME DESTINATION bin
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib
)
install(FILES ${headers} DESTINATION include/humblelogging)

# Examples
macro(humblelogging_POSTBUILD_COPY target_)
	add_custom_command(
		TARGET ${target_} POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_if_different
			$<TARGET_FILE:humblelogging>
			$<TARGET_FILE_DIR:${target_}>/$<TARGET_FILE_NAME:humblelogging>
	)
endmacro(humblelogging_POSTBUILD_COPY)

if(BuildExamples)
	add_subdirectory(examples/basic)
	add_subdirectory(examples/pattern_formatter)
	add_subdirectory(examples/configured)
	add_subdirectory(examples/mtperformance)
	if(WIN32)
		add_subdirectory(examples/threaded)
	endif(WIN32)
	add_subdirectory(examples/log_level_test)
endif(BuildExamples)
