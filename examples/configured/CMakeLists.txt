set(configured_example_sources
  configured_example.cpp
)
include_directories(../../include)
add_executable(configured_example ${configured_example_sources})
target_link_libraries(configured_example humblelogging)
humblelogging_POSTBUILD_COPY(configured_example)