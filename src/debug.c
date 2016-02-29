#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "main.h"
#include "main_menu.h"
#include "debug.h"

void init_debug() {
	/* background color and main loop functions */
	SDL_FillRect(screen, NULL,
				 SDL_MapRGBA(screen->format,
							 0x00, 0x00, 0x00, 0xFF));
	poll_events = debug_poll_events;
	update = debug_update;
	render = debug_render;
	/* end background color and main loop functions */

	destroy_main_menu();
}

void debug_poll_events(SDL_Event* event)
{
	while (SDL_PollEvent(event) != 0) {
		if (event->type == SDL_QUIT)
		{
			exit_SDL = 1;
		}
		else if (event->type == SDL_KEYDOWN)
		{
			switch (event->key.keysym.sym)
			{
			case SDLK_ESCAPE:
				exit_SDL = 1;
				break;
			}
		} else if (event->type == SDL_MOUSEBUTTONDOWN) {

		} else if (event->type == SDL_MOUSEBUTTONUP) {

		}
	}
}

void debug_update(void)
{
	
}

void debug_render(void)
{

}

void destroy_debug() {

}
