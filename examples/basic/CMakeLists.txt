set(basic_example_sources
  basic_example.cpp
)
include_directories(../../include)
add_executable(basic_example ${basic_example_sources})
target_link_libraries(basic_example humblelogging)

add_custom_command(TARGET basic_example POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
  $<TARGET_FILE_DIR:humblelogging>
  $<TARGET_FILE_DIR:basic_example>
)
