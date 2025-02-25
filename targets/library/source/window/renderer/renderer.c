#include "renderer.h"
#include <SFML/Graphics.h>
#include "window/window.h"
#include "sub_renderers/grid/grid.h"
#include "sub_renderers/splines/splines.h"

void render(void)
{	sfRenderWindow_clear(window, sfBlack);
	render_grid();
	render_splines();
	sfRenderWindow_display(window);
}
