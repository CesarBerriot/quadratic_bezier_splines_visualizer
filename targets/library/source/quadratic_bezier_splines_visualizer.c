#include "quadratic_bezier_splines_visualizer.h"
#include "window/window.h"
#include "spline_registry/spline_registry.h"

void qbsv_add_spline(struct qbs_point spline[], int length, struct qbsv_color color)
{	register_spline(spline, length, color);
}

void qbsv_run(void)
{	window_initialize();
	window_run();
	window_cleanup();
}

void qbsv_reset(void)
{	cleanup_spline_registry();
}
