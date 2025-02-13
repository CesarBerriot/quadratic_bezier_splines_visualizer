#include "splines.h"
#include <SFML/Graphics.h>
#include <math.h>
#include "window/window.h"
#include "spline_registry/spline_registry.h"
#include "math/math.h"

static void render_spline(struct spline_registry_node);
static void render_point(struct qbs_point);
static sfVector2f convert_position(struct qbs_vector2);
static sfColor convert_color(struct qbsv_color);
static void render_segment(sfVector2f, sfVector2f, sfColor);

void render_splines(void)
{	for(struct spline_registry_node * iterator = spline_registry; iterator; iterator = iterator->next_node)
		render_spline(*iterator);
}

static void render_spline(struct spline_registry_node node)
{	for(int i = 0; i < node.length; ++i)
		render_point(node.spline[i]);
	float min = node.spline[0].position.x;
	float max = node.spline[node.length - 1].position.x;
	float total_distance = max - min;
	int point_count = round(20 * total_distance);
	float step = total_distance / point_count;
	for(int i = 1; i <= point_count; ++i)
	{	float origin_delta = min + step * (i - 1);
		float destination_delta = min + step * i;
		struct qbs_vector2 origin = qbs_compute_position(origin_delta, node.spline, node.length);
		struct qbs_vector2 destination = qbs_compute_position(destination_delta, node.spline, node.length);
		render_segment(convert_position(origin), convert_position(destination), convert_color(node.color));
	}
}

static void render_point(struct qbs_point point)
{	float radius = .02;

	struct circle_colors { sfColor fill, outline; };

	struct { struct circle_colors position, influence; } colors =
	{	.position =
		{	.fill = sfBlack,
			.outline = sfWhite
		},
		.influence =
		{	.fill = sfWhite,
			.outline = sfBlack
		}
	};

	sfCircleShape * circle = sfCircleShape_create();
	sfCircleShape_setRadius(circle, radius);
	sfCircleShape_setOrigin(circle, (sfVector2f){ .x = radius, .y = radius });
	sfCircleShape_setOutlineThickness(circle, radius / 3);

	sfVector2f point_position = convert_position(point.position);

	sfCircleShape_setPosition(circle, point_position);
	sfCircleShape_setFillColor(circle, colors.position.fill);
	sfCircleShape_setOutlineColor(circle, colors.position.outline);
	sfRenderWindow_drawCircleShape(window, circle, NULL);

	sfVector2f influence_position =
	{	.x = point.position.x + point.influence_point_offset.x,
		.y = point.position.y + point.influence_point_offset.y
	};

	sfCircleShape_setPosition(circle, influence_position);
	sfCircleShape_setFillColor(circle, colors.influence.fill);
	sfCircleShape_setOutlineColor(circle, colors.influence.outline);
	sfRenderWindow_drawCircleShape(window, circle, NULL);

	sfCircleShape_destroy(circle);

	render_segment(point_position, influence_position, sfYellow);
}

static sfVector2f convert_position(struct qbs_vector2 position)
{	return (sfVector2f)
	{	.x = position.x,
		.y = position.y
	};
}

static sfColor convert_color(struct qbsv_color color)
{	return (sfColor)
	{	.r = color.r,
		.g = color.g,
		.b = color.b,
		.a = 255
	};
}

static void render_segment(sfVector2f origin, sfVector2f destination, sfColor color)
{	sfVector2f direction = math_subtract_vectors(destination, origin);
	float length = math_compute_vector_length(direction);
	float angle = math_compute_vector_angle(direction);

	sfVector2f size = { .x = .01, .y = length };

	sfRectangleShape * rectangle = sfRectangleShape_create();
	sfRectangleShape_setOrigin(rectangle, (sfVector2f){ .x = size.x / 2 });
	sfRectangleShape_setPosition(rectangle, origin);
	sfRectangleShape_setOutlineThickness(rectangle, .003);
	sfRectangleShape_setOutlineColor(rectangle, sfBlack);
	sfRectangleShape_setFillColor(rectangle, color);
	sfRectangleShape_setRotation(rectangle, -angle);
	sfRectangleShape_setSize(rectangle, size);

	sfRenderWindow_drawRectangleShape(window, rectangle, NULL);

	sfRectangleShape_destroy(rectangle);
}
