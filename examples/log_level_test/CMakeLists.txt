set(log_level_test_sources
  log_level_test.cpp
)
include_directories(../../include)
add_executable(log_level_test ${log_level_test_sources})
target_link_libraries(log_level_test humblelogging)
humblelogging_POSTBUILD_COPY(log_level_test)
