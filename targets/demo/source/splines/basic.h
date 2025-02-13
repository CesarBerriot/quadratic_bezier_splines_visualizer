static struct qbs_point basic_spline[] =
{	{	.position = { 0 },
		.influence_point_offset = { .x = .4 }
	},
	{	.position = { .x = 1, .y = 1 },
		.influence_point_offset = { .x = -.4 }
	}
};

enum { basic_spline_length = sizeof(basic_spline) / sizeof(struct qbs_point) };