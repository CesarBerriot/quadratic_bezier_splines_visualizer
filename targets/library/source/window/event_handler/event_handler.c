#include "event_handler.h"
#include <SFML/Graphics.h>
#include <stdbool.h>
#include "window/window.h"

void handle_events(void)
{	sfEvent event;
	while(sfWindow_pollEvent(window, &event))
		switch(event.type)
		{	case sfEvtMouseMoved:
				{	static struct
					{	bool computed;
						sfMouseMoveEvent event;
					} last;

					if(!last.computed)
						last.event = event.mouseMove;

					if(sfMouse_isButtonPressed(sfMouseLeft) || sfMouse_isButtonPressed(sfMouseMiddle) || sfMouse_isButtonPressed(sfMouseRight))
					{	float sensitivity = .001;
						float scale_factor = -(sensitivity / window_view_data.zoom_level);
						window_view_data.position.x += (event.mouseMove.x - last.event.x) * scale_factor;
						window_view_data.position.y += (event.mouseMove.y - last.event.y) * scale_factor;
						window_recompute_view();
					}

					last.event = event.mouseMove;
					last.computed = true;

					break;
				}
			case sfEvtMouseWheelScrolled:
				{	float sensitivity = .1;
					window_view_data.zoom_level += window_view_data.zoom_level * event.mouseWheelScroll.delta * sensitivity;
					window_recompute_view();
					break;
				}
			case sfEvtResized:
				window_recompute_view();
				break;
			case sfEvtClosed:
				sfRenderWindow_close(window);
				break;
		}
}
