#include <stdlib.h>
#include <quadratic_bezier_splines_visualizer.h>
#include <windows.h>
#include <hard_assert.h>

static struct qbs_point spline[] =
{	{	.position = { 0 },
		.influence_point_offset = { .x = .4 }
	},
	{	.position = { .x = 1, .y = 1 },
		.influence_point_offset = { .x = -.4 }
	}
};

enum { spline_length = sizeof(spline) / sizeof(struct qbs_point) };

int main(void)
{	ha_assert(qbs_validate_spline(spline, spline_length), "Demo", "Spline Validation Failure.");

	for(int i = 0; i < 2; ++i)
	{	qbsv_add_spline(spline, spline_length, (struct qbsv_color){ .r = 255 });
		qbsv_run();
		qbsv_reset();
	}
	return EXIT_SUCCESS;
}
