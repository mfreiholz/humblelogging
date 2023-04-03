cmake_minimum_required(VERSION 3.14)

project(
	humblelogging
	VERSION 0.0.0
	DESCRIPTION "HumbleLogging is a lightweight C++ logging framework. It aims to be extendible, easy to understand and as fast as possible."
	HOMEPAGE_URL "https://github.com/mfreiholz/humblelogging"
)

#
# Options
#

option(BuildShared "BuildShared" OFF)
option(BuildTests "BuildTests" OFF)
option(BuildApps "BuildApps" ON)

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
	${PROJECT_SOURCE_DIR}/libs/humblelogging/include/humblelogging/version.h
)

#
# Third Party Libraries / Dependencies
# All of them should be optional.
#

if(BuildTests)
	include(thirdparty/googletest.cmake)
endif(BuildTests)

# Apps
macro(humblelogging_POSTBUILD_COPY target_)
	add_custom_command(
		TARGET ${target_} POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_if_different
			$<TARGET_FILE:humblelogging>
			$<TARGET_FILE_DIR:${target_}>/$<TARGET_FILE_NAME:humblelogging>
	)
endmacro(humblelogging_POSTBUILD_COPY)

add_subdirectory(libs/humblelogging)

if(BuildApps)
	add_subdirectory(apps/basic_example)
	add_subdirectory(apps/benchmark)
endif(BuildApps)

# Unit Testing
if(BuildTests)
	add_subdirectory(tests)
endif(BuildTests)