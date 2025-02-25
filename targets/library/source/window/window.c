#include "window.h"
#include <stdbool.h>
#include "event_handler/event_handler.h"
#include "renderer/renderer.h"

sfRenderWindow * window;
sfContextSettings context_settings = { .antialiasingLevel = 16 };

struct window_view_data window_view_data;

static struct window_view_data default_view_data =
{	.zoom_level = 1,
	.position = { .x = 0, .y = 0 }
};

void window_initialize(void)
{	window_view_data = default_view_data;
	window = sfRenderWindow_create((sfVideoMode){ .width = 900, .height = 900 }, "Cubic Bezier Splines Visualizer", sfDefaultStyle, &context_settings);
	sfRenderWindow_setVerticalSyncEnabled(window, true);
	window_recompute_view();
}

void window_run(void)
{	while(sfRenderWindow_isOpen(window))
	{   handle_events();
		render();
	}
}

void window_cleanup(void)
{	sfRenderWindow_destroy(window);
}

void window_recompute_view(void)
{	sfVector2u window_size = sfWindow_getSize(window);
	float shorter_window_side = window_size.x < window_size.y ? window_size.x : window_size.y;

	sfVector2f view_size =
	{	.x = window_size.x / shorter_window_side / window_view_data.zoom_level,
		.y = -(window_size.y / shorter_window_side / window_view_data.zoom_level)
	};

	sfVector2f view_position =
	{	.x = .5 + window_view_data.position.x,
		.y = .5 - window_view_data.position.y
	};

	sfView * view = sfView_create();
	sfView_setSize(view, view_size);
	sfView_setCenter(view, view_position);
	sfRenderWindow_setView(window, view);
	sfView_destroy(view);
}
