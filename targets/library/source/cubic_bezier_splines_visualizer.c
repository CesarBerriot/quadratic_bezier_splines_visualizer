#include "cubic_bezier_splines_visualizer.h"
#include "window/window.h"
#include "spline_registry/spline_registry.h"

void cbsv_add_spline(struct cbs_point spline[], int length, struct cbsv_color color)
{	register_spline(spline, length, color);
}

void cbsv_run(void)
{	window_initialize();
	window_run();
	window_cleanup();
}

void cbsv_reset(void)
{	cleanup_spline_registry();
}
