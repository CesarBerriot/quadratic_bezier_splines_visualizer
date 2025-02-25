#include <SFML/Graphics.h>

extern sfRenderWindow * window;
extern sfContextSettings context_settings;

extern struct window_view_data
{	float zoom_level;
	sfVector2f position;
} window_view_data;

void window_initialize(void);
void window_run(void);
void window_cleanup(void);
void window_recompute_view(void);
