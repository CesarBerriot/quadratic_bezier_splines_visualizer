static struct cbs_point green_spline[] =
{	{	.position = { 0 },
		.influence_point_offset = { .x = -.4 }
	},
	{	.position = { .x = .8, .y = 1.2 },
		.influence_point_offset = { .x = -.1 }
	},
	{	.position = { .x = 1, .y = 1 },
		.influence_point_offset = { .x = -.1 }
	},
	{	.position = { .x = 1.3, .y = .7 },
		.influence_point_offset = { .x = -.1, .y = -.17 }
	}
};

enum { green_spline_length = sizeof(green_spline) / sizeof(struct cbs_point) };
