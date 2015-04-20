set(threaded_example_sources
  threaded_example.cpp
)
include_directories(../../include)
add_executable(threaded_example ${threaded_example_sources})
target_link_libraries(threaded_example humblelogging)
humblelogging_POSTBUILD_COPY(threaded_example)
