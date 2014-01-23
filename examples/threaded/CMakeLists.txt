set(threaded_example_sources
  threaded_example.cpp
)
include_directories(../../include)
add_executable(threaded_example ${threaded_example_sources})
target_link_libraries(threaded_example humblelogging)

add_custom_command(TARGET threaded_example POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
  $<TARGET_FILE_DIR:humblelogging>
  $<TARGET_FILE_DIR:threaded_example>
)
