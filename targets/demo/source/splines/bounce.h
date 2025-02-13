static struct qbs_point bounce_spline[] =
{	{	.position = { 0 },
		//.influence_point_offset = { .x = .4 }
		.influence_point_offset = { 0 }
	},
	{	.position = { .x = .9, .y = 1 },
		//.influence_point_offset = { .x = .3 }
		.influence_point_offset = { 0 }
	},
	{	.position = { .x = 1, .y = 1 },
		//.influence_point_offset = { .x = -.4 }
		.influence_point_offset = { 0 }
	},
};

enum { bounce_spline_length = sizeof(bounce_spline) / sizeof(struct qbs_point) };