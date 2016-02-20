#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "main.h"
#include "splash_screen.h"

void init_splash_screen() {
	SDL_FillRect(screen, NULL,
				 SDL_MapRGBA(screen->format,
							 0x00, 0x00, 0x22, 0xFF));
	total_ticks = 0;
	poll_events = splash_screen_poll_events;
	update = splash_screen_update;
	render = splash_screen_render;

}

void splash_screen_poll_events(SDL_Event* event) {
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

void splash_screen_update(void) {
	/* Keep track of how long the splash screen has been displayed */
	total_ticks += delta;
	if ((total_ticks / ticks_per_frame) / fps >= 3000) {
		exit(0);
	}
	/* End keep track of how long the splash screen has been displayed */
}

void splash_screen_render(void) {
	SDL_BlitSurface(splash_screen, NULL, screen, NULL);
}
