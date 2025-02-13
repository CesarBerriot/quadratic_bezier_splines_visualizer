#include "renderer.h"
#include <SFML/Graphics.h>
#include "window/window.h"
#include "sub_renderers/splines/splines.h"

void render(void)
{	sfRenderWindow_clear(window, sfBlack);

	sfRectangleShape * square = sfRectangleShape_create();

	sfRectangleShape_setFillColor(square, sfRed);
	sfRectangleShape_setPosition(square, (sfVector2f){ 0 });
	sfRectangleShape_setSize(square, (sfVector2f){ .x = 1, .y = 1 });
	sfRenderWindow_drawRectangleShape(window, square, NULL);

	sfRectangleShape_setFillColor(square, sfWhite);
	sfRectangleShape_setPosition(square, (sfVector2f){ .x = .45, .y = .45 });
	sfRectangleShape_setSize(square, (sfVector2f){ .x = .1, .y = .1 });
	sfRenderWindow_drawRectangleShape(window, square, NULL);

	sfRectangleShape_destroy(square);

	render_splines();

	sfRenderWindow_display(window);
}
