set(performance_example_sources performance_example.cpp)
include_directories(../../include)
add_executable(performance_example ${performance_example_sources})
target_link_libraries(performance_example humblelogging)
