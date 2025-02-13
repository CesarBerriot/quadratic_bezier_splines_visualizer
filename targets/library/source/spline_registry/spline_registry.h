#include "quadratic_bezier_splines_visualizer.h"

extern struct spline_registry_node
{	struct qbs_point * spline;
	int length;
	struct qbsv_color color;
	struct spline_registry_node * next_node;
} * spline_registry;

void register_spline(struct qbs_point spline[], int length, struct qbsv_color color);
void cleanup_spline_registry(void);
