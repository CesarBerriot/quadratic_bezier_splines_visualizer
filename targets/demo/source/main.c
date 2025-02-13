#include <stdlib.h>
#include <quadratic_bezier_splines_visualizer.h>
#include <windows.h>
#include <hard_assert.h>
#include "splines/basic.h"
#include "splines/bounce.h"

struct
{	struct qbs_point * spline;
	int length;
	struct qbsv_color color;
} splines[] =
{	{	.spline = basic_spline,
		.length = basic_spline_length,
		.color = { .r = 255 }
	},
	{	.spline = bounce_spline,
		.length = bounce_spline_length,
		.color = { .g = 255 }
	}
};

enum { splines_length = sizeof(splines) / sizeof(splines[0]) };

int main(void)
{	for(int i = 0; i < splines_length; ++i)
		ha_assert(qbs_validate_spline(splines[i].spline, splines[i].length), "Demo", "Spline Validation Failure.");

	for(int i = 0; i < 2; ++i)
	{	for(int i = 0; i < splines_length; ++i)
			qbsv_add_spline(splines[i].spline, splines[i].length, splines[i].color);
		qbsv_run();
		qbsv_reset();
	}
	return EXIT_SUCCESS;
}
