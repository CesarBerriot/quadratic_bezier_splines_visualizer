#include "cubic_bezier_splines_visualizer.h"

extern struct spline_registry_node
{	struct
    {   struct cbs_point * array;
        int length;
    } points;
	struct cbsv_color color;
    struct cbs_spline * handle;
	struct spline_registry_node * next_node;
} * spline_registry;

void register_spline(struct cbs_point spline[], int length, struct cbsv_color color);
void cleanup_spline_registry(void);
