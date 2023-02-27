cmake_minimum_required(VERSION 3.14)

project(
	humblelogging
	VERSION 4.0.0
	DESCRIPTION "HumbleLogging is a lightweight C++ logging framework. It aims to be extendible, easy to understand and as fast as possible."
	HOMEPAGE_URL "https://github.com/mfreiholz/humblelogging"
)

#
# Options
#

option(BuildShared "BuildShared" OFF)
option(BuildTests "BuildTests" OFF)
option(BuildApps "BuildApps" ON)

if(BuildShared)
	set(StaticOrShared "SHARED")
	add_definitions(-DHUMBLELOGGING_EXPORT)
else(BuildShared)
	set(StaticOrShared "STATIC")
endif(BuildShared)

if(WIN32)
	add_definitions(/Zc:wchar_t-)
	add_definitions(/INCREMENTAL:NO)
	add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif(WIN32)

if(CMAKE_COMPILER_IS_GNUCXX)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")
endif(CMAKE_COMPILER_IS_GNUCXX)

set(CMAKE_CXX_STANDARD 17)

configure_file(
	${PROJECT_SOURCE_DIR}/version.h.in
	${PROJECT_SOURCE_DIR}/include/humblelogging/version.h
)

#
# Third Party Libraries / Dependencies
# All of them should be optional.
#

if(BuildTests)
	include(thirdparty/googletest.cmake)
endif(BuildTests)

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
	include/humblelogging/util/patternconfigregistry.h
	include/humblelogging/util/processinfo.h
	include/humblelogging/util/ternarytree.h
	include/humblelogging/util/fmt.h
	include/humblelogging/appender.h
	include/humblelogging/configuration.h
	include/humblelogging/defines.h
	include/humblelogging/factory.h
	include/humblelogging/formatter.h
	include/humblelogging/humblelogging.h
	include/humblelogging/logevent.h
	include/humblelogging/logger.h
	include/humblelogging/loglevel.h
	include/humblelogging/version.h
)

set(sources
	src/appender/consoleappender.cpp
	src/appender/fileappender.cpp
	src/appender/nullappender.cpp
	src/appender/rollingfileappender.cpp
	src/formatter/simpleformatter.cpp
	src/formatter/patternformatter.cpp
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
#if(BuildLockFree)
#	list(APPEND sources src/util/mutex_nolock.cpp)
#	list(APPEND sources src/util/spinlock_nolock.cpp)
#else()
#	if(BuildSystemNative)
#		if(WIN32)
#			list(APPEND sources src/util/mutex_windows_native.cpp)
#			list(APPEND sources src/util/spinlock_windows_native.cpp)
#		endif()
#		if(UNIX)
#			list(APPEND sources src/util/mutex_linux_native.cpp)
#			list(APPEND sources src/util/spinlock_linux_native.cpp)
#		endif()
#	else()
#		#if(UNIX)
#		#	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
#		#endif()
#		list(APPEND sources src/util/mutex_c11.cpp)
#		list(APPEND sources src/util/spinlock_c11.cpp)
#	endif()
#endif()

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

#if(BuildSystemNative)
#	if(UNIX)
#		target_link_libraries(${PROJECT_NAME} pthread)
#	endif()
#endif()

#
# Install
#

install(TARGETS humblelogging
	RUNTIME DESTINATION bin
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib
)
install(FILES ${headers} DESTINATION include/humblelogging)

# Apps
macro(humblelogging_POSTBUILD_COPY target_)
	add_custom_command(
		TARGET ${target_} POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_if_different
			$<TARGET_FILE:humblelogging>
			$<TARGET_FILE_DIR:${target_}>/$<TARGET_FILE_NAME:humblelogging>
	)
endmacro(humblelogging_POSTBUILD_COPY)

if(BuildApps)
	add_subdirectory(apps/basic_example)
	add_subdirectory(apps/benchmark)
endif(BuildApps)

# Unit Testing
if(BuildTests)
	add_subdirectory(tests)
endif(BuildTests)