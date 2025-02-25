static struct cbs_point red_spline[] =
{	{	.position = { .x = -.2, .y = .7 },
		.influence_point_offset = { .x = -.2, .y = -.3 }
	},
	{	.position = { .x = .85, .y = .4 },
		.influence_point_offset = { .y = -.2 }
	},
	{	.position = { .x = .6, .y = -.3 },
		.influence_point_offset = { .x = -.2, .y = .2 }
	},
	{	.position = { .x = 1.6, .y = -.5 },
		.influence_point_offset = { .x = .4, .y = .5 }
	}
};

enum { red_spline_length = sizeof(red_spline) / sizeof(struct cbs_point) };
