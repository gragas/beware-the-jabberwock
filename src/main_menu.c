#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "main.h"
#include "main_menu.h"

void init_main_menu() {
	SDL_FillRect(screen, NULL,
				 SDL_MapRGBA(screen->format,
							 0x33, 0x00, 0x00, 0xFF));
	poll_events = main_menu_poll_events;
	update = main_menu_update;
	render = main_menu_render;
}

void main_menu_poll_events(SDL_Event* event) {
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
		}
	}
}

void main_menu_update(void) {

}

void main_menu_render(void) {
	SDL_BlitSurface(main_menu, NULL, screen, NULL);
}
