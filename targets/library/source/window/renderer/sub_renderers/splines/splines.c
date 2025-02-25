#include "splines.h"
#include <SFML/Graphics.h>
#include <math.h>
#include <stdbool.h>
#include "window/window.h"
#include "spline_registry/spline_registry.h"
#include "math/math.h"

enum layer
{   LAYER_SPLINES,
	LAYER_INFLUENCE_SEGMENTS,
	LAYER_POINTS,
	LAYER_MAX
};

static sfRenderTexture * layers[LAYER_MAX];

static void render_spline(struct spline_registry_node);
static void render_point(struct cbs_point);
static sfVector2f convert_position(struct cbs_vector2);
static sfColor convert_color(struct cbsv_color);
static void render_segment(sfVector2f, sfVector2f, float width, sfColor, enum layer);
static void setup_layers(void);
static void render_layers(void);
static void cleanup_layers(void);
static void apply_standard_window_view(void);

void render_splines(void)
{	setup_layers();
	for(struct spline_registry_node * iterator = spline_registry; iterator; iterator = iterator->next_node)
		render_spline(*iterator);
	render_layers();
	cleanup_layers();
}

static void render_spline(struct spline_registry_node node)
{	float width = .01;
	for(int i = 0; i < node.points.length; ++i)
		render_point(node.points.array[i]);
	float total_distance = cbs_get_spline_length(node.handle);
	int segment_count = round(40 * total_distance);
	float step = total_distance / segment_count;
	for(int i = 1; i <= segment_count; ++i)
	{	float origin_delta = step * (i - 1);
		float destination_delta = step * i;
		struct cbs_vector2 origin = cbs_compute_position(origin_delta, node.handle);
		struct cbs_vector2 destination = cbs_compute_position(destination_delta, node.handle);
		render_segment(convert_position(origin), convert_position(destination), width, convert_color(node.color), LAYER_SPLINES);
	}
}

static void render_point(struct cbs_point point)
{	float radius = .015;
	float influence_scale = .75;

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
	sfRenderTexture_drawCircleShape(layers[LAYER_POINTS], circle, NULL);

	sfVector2f influence_position =
	{	.x = point.position.x + point.influence_point_offset.x,
		.y = point.position.y + point.influence_point_offset.y
	};

	sfVector2f inverted_influence_position =
	{	.x = point.position.x - point.influence_point_offset.x,
		.y = point.position.y - point.influence_point_offset.y
	};

	sfCircleShape_scale(circle, (sfVector2f){ .x = influence_scale, .y = influence_scale });
	sfCircleShape_setFillColor(circle, colors.influence.fill);
	sfCircleShape_setOutlineColor(circle, colors.influence.outline);

	sfCircleShape_setPosition(circle, influence_position);
	sfRenderTexture_drawCircleShape(layers[LAYER_POINTS], circle, NULL);

	sfCircleShape_setPosition(circle, inverted_influence_position);
	sfRenderTexture_drawCircleShape(layers[LAYER_POINTS], circle, NULL);

	sfCircleShape_destroy(circle);

	float influence_segment_width = .0075;
	render_segment(influence_position, inverted_influence_position, influence_segment_width, sfYellow, LAYER_INFLUENCE_SEGMENTS);
}

static sfVector2f convert_position(struct cbs_vector2 position)
{	return (sfVector2f)
	{	.x = position.x,
		.y = position.y
	};
}

static sfColor convert_color(struct cbsv_color color)
{	return (sfColor)
	{	.r = color.r,
		.g = color.g,
		.b = color.b,
		.a = 255
	};
}

static void render_segment(sfVector2f origin, sfVector2f destination, float width, sfColor color, enum layer layer)
{	sfVector2f direction = math_subtract_vectors(destination, origin);
	float length = math_compute_vector_length(direction);
	float angle = math_compute_vector_angle(direction);
	float outline_scale_factor = 1.6;

	sfRectangleShape * rectangle = sfRectangleShape_create();
	sfRectangleShape_setOrigin(rectangle, (sfVector2f){ .x = width / 2 });
	sfRectangleShape_setPosition(rectangle, origin);
	sfRectangleShape_setSize(rectangle, (sfVector2f){ .x = width, .y = length });
	sfRectangleShape_setRotation(rectangle, -angle);

	sfRectangleShape_setFillColor(rectangle, sfBlack);
	sfRectangleShape_scale(rectangle, (sfVector2f){ .x = outline_scale_factor, .y = 1 });
	sfRenderTexture_drawRectangleShape(layers[layer], rectangle, NULL);

	sfRectangleShape_setFillColor(rectangle, color);
	sfRectangleShape_setScale(rectangle, (sfVector2f){ .x = 1, .y = 1 });
	sfRenderTexture_drawRectangleShape(layers[layer], rectangle, NULL);

	sfRectangleShape_destroy(rectangle);
}

static void setup_layers(void)
{	for(int i = 0; i < LAYER_MAX; ++i)
	{   sfRenderTexture * layer = sfRenderTexture_createWithSettings(sfWindow_getSize(window).x, sfWindow_getSize(window).y, &context_settings);
		sfRenderTexture_setView(layer, sfRenderWindow_getView(window));
		layers[i] = layer;
	}
}

static void render_layers(void)
{	sfView * window_view_backup = sfView_copy(sfRenderWindow_getView(window));
	apply_standard_window_view();
	for(int i = 0; i < LAYER_MAX; ++i)
	{   sfRenderTexture * layer = layers[i];
		sfRenderTexture_display(layer);

		sfSprite * sprite = sfSprite_create();
		sfSprite_setTexture(sprite,  sfRenderTexture_getTexture(layer), true);

		// SFML bug workaround
		sfRenderTexture * throwaway_render_texture = sfRenderTexture_createWithSettings(1, 1, NULL);
		sfRenderTexture_drawSprite(throwaway_render_texture, sprite, NULL);
		sfRenderTexture_destroy(throwaway_render_texture);

		sfRenderWindow_drawSprite(window, sprite, NULL);
		sfSprite_destroy(sprite);
	}
	sfRenderWindow_setView(window, window_view_backup);
	sfView_destroy(window_view_backup);
}

static void cleanup_layers(void)
{	for(int i = 0; i < LAYER_MAX; ++i)
		sfRenderTexture_destroy(layers[i]);
}

static void apply_standard_window_view(void)
{	sfView * standard_window_view = sfView_create();
	sfVector2u window_size = sfRenderWindow_getSize(window);
	sfView_setSize(standard_window_view, (sfVector2f){ .x = window_size.x, .y = window_size.y });
	sfView_setCenter(standard_window_view, (sfVector2f){ .x = window_size.x / 2., .y = window_size.y / 2. });
	sfRenderWindow_setView(window, standard_window_view);
	sfView_destroy(standard_window_view);
}
