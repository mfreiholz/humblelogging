set(library_name humblelogging)
set(library_include_dir ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(library_src_dir ${CMAKE_CURRENT_SOURCE_DIR}/src)

set(headers
	${library_include_dir}/${library_name}/appender/consoleappender.h
	${library_include_dir}/${library_name}/appender/fileappender.h
	${library_include_dir}/${library_name}/appender/nullappender.h
	${library_include_dir}/${library_name}/appender/rollingfileappender.h
	${library_include_dir}/${library_name}/formatter/simpleformatter.h
	${library_include_dir}/${library_name}/formatter/patternformatter.h
	${library_include_dir}/${library_name}/util/patternconfigregistry.h
	${library_include_dir}/${library_name}/util/processinfo.h
	${library_include_dir}/${library_name}/util/ternarytree.h
	${library_include_dir}/${library_name}/util/fmt.h
	${library_include_dir}/${library_name}/appender.h
	${library_include_dir}/${library_name}/configuration.h
	${library_include_dir}/${library_name}/defines.h
	${library_include_dir}/${library_name}/factory.h
	${library_include_dir}/${library_name}/formatter.h
	${library_include_dir}/${library_name}/humblelogging.h
	${library_include_dir}/${library_name}/logevent.h
	${library_include_dir}/${library_name}/logger.h
	${library_include_dir}/${library_name}/loglevel.h
	${library_include_dir}/${library_name}/version.h
)

set(sources
	${library_src_dir}/appender/consoleappender.cpp
	${library_src_dir}/appender/fileappender.cpp
	${library_src_dir}/appender/nullappender.cpp
	${library_src_dir}/appender/rollingfileappender.cpp
	${library_src_dir}/formatter/simpleformatter.cpp
	${library_src_dir}/formatter/patternformatter.cpp
	${library_src_dir}/util/patternconfigregistry.cpp
	${library_src_dir}/util/processinfo.cpp
	${library_src_dir}/appender.cpp
	${library_src_dir}/configuration.cpp
	${library_src_dir}/factory.cpp
	${library_src_dir}/formatter.cpp
	${library_src_dir}/logevent.cpp
	${library_src_dir}/logger.cpp
	${library_src_dir}/loglevel.cpp
)

if(BuildShared)
	set(StaticOrShared "SHARED")
	add_definitions(-DHUMBLELOGGING_EXPORT)
else(BuildShared)
	set(StaticOrShared "STATIC")
endif(BuildShared)

add_library(
	${library_name}
	${StaticOrShared}
	${sources}
	${headers}
)

target_include_directories(
	${library_name}
	PUBLIC ${library_include_dir}
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${headers} ${sources})

install(
	TARGETS ${library_name}
	RUNTIME DESTINATION bin
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib
)

install(
	DIRECTORY ${library_include_dir}/${library_name}
	DESTINATION include
)