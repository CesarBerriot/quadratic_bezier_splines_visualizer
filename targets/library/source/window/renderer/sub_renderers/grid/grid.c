#include "grid.h"
#include <math.h>
#include <stdbool.h>
#include "window/window.h"

static struct
{	sfVector2f view_center;
	sfVector2f view_size_half;
} cache;

static void compute_cache(void);
static void render_lines(bool vertical);
static float get_opposite_axis_value(sfVector2f vector, bool vertical);
static void set_opposite_axis_value(sfVector2f *vector, bool vertical, float value);
static void render_line(sfVector2f, float origin, float destination, bool primary, bool vertical);

void render_grid(void)
{	compute_cache();
	render_lines(false);
	render_lines(true);
}

static void compute_cache(void)
{	sfView const * view = sfRenderWindow_getView(window);
	cache.view_center = sfView_getCenter(view);
	sfVector2f view_size = sfView_getSize(view);
	cache.view_size_half = (sfVector2f){ .x = view_size.x / 2, .y = fabs(view_size.y) / 2 };
}

static void render_lines(bool vertical)
{	float center = get_opposite_axis_value(cache.view_center, vertical);
	float size_half = get_opposite_axis_value(cache.view_size_half, vertical);

	float origin = center - size_half;
	float destination = center + size_half;

	float opposite_axis_center = get_opposite_axis_value(cache.view_center, !vertical);
	float opposite_axis_size_half = get_opposite_axis_value(cache.view_size_half, !vertical);
	float opposite_axis_origin = opposite_axis_center - opposite_axis_size_half;
	float opposite_axis_destination = opposite_axis_center + opposite_axis_size_half;


	float step = .1;
	float one_out_of_step = 1 / step;

	float origin_ceiled = ceil(origin * one_out_of_step) / one_out_of_step;

	for(float i = origin_ceiled; i < destination; i = round((i + step) * 10) / 10)
	{	sfVector2f position;
		set_opposite_axis_value(&position, !vertical, opposite_axis_center);
		set_opposite_axis_value(&position, vertical, i);
		bool primary = !(i - floor(i));
		render_line(position, opposite_axis_origin, opposite_axis_destination, primary, vertical);
	}
}

static float get_opposite_axis_value(sfVector2f vector, bool vertical)
{	return vertical ? vector.x : vector.y;
}

static void set_opposite_axis_value(sfVector2f * vector, bool vertical, float value)
{	*(vertical ? &vector->x : &vector->y) = value;
}

static void render_line(sfVector2f position, float origin, float destination, bool primary, bool vertical)
{	float width = primary ? .012 : .004;
	sfColor color = sfColor_fromRGB(100, 100, 100);

	sfVector2f rectangle_size = { .x = destination - origin, .y = width };
	sfVector2f rectangle_size_half = { .x = rectangle_size.x / 2, .y = rectangle_size.y / 2 };

	sfRectangleShape * rectangle = sfRectangleShape_create();
	sfRectangleShape_setFillColor(rectangle, color);
	sfRectangleShape_setSize(rectangle, rectangle_size);
	sfRectangleShape_setOrigin(rectangle, rectangle_size_half);
	if(vertical)
		sfRectangleShape_setRotation(rectangle, 90);
	sfRectangleShape_setPosition(rectangle, position);
	sfRenderWindow_drawRectangleShape(window, rectangle, NULL);
	sfRectangleShape_destroy(rectangle);
}
