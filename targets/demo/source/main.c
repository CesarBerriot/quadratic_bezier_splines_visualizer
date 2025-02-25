#include <stdlib.h>
#include <cubic_bezier_splines_visualizer.h>
#include "splines/red.h"
#include "splines/green.h"

struct
{	struct cbs_point * spline;
	int length;
	struct cbsv_color color;
} splines[] =
{	{	.spline = red_spline,
		.length = red_spline_length,
		.color = { .r = 255 }
	},
	{	.spline = green_spline,
		.length = green_spline_length,
		.color = { .g = 255 }
	}
};

enum { splines_length = sizeof(splines) / sizeof(splines[0]) };

int main(void)
{	for(int i = 0; i < 2; ++i)
	{	for(int i = 0; i < splines_length; ++i)
			cbsv_add_spline(splines[i].spline, splines[i].length, splines[i].color);
		cbsv_run();
		cbsv_reset();
	}
	return EXIT_SUCCESS;
}
