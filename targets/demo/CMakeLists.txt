include(cmake/hard_assert.cmake)

add_executable(quadratic_bezier_splines_visualizer_demo WIN32 source/main.c)
target_link_libraries(quadratic_bezier_splines_visualizer_demo PRIVATE quadratic_bezier_splines_visualizer hard_assert)
