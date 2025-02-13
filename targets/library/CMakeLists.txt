include(cmake/csfml.cmake)
include(cmake/quadratic_bezier_splines.cmake)

add_library(
        quadratic_bezier_splines_visualizer STATIC
        source/quadratic_bezier_splines_visualizer.c
        source/window/window.c
        source/window/event_handler/event_handler.c
        source/window/renderer/renderer.c
        source/window/renderer/sub_renderers/splines/splines.c
        source/spline_registry/spline_registry.c
        source/math/math.c
)
target_include_directories(quadratic_bezier_splines_visualizer PUBLIC source/include PRIVATE source)
link_csfml(quadratic_bezier_splines_visualizer)
target_link_libraries(quadratic_bezier_splines_visualizer PUBLIC quadratic_bezier_splines)