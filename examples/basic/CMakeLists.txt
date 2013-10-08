set(basic_example_sources
  basic_example.cpp
)
include_directories(../../include)
add_executable(basic_example ${basic_example_sources})
target_link_libraries(basic_example humblelogging)