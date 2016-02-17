#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "main.h"
#include "splash_screen.h"

int total_ticks = 0;

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
	total_ticks += delta;
	if ((total_ticks / ticks_per_frame) / fps >= 3000) {
		exit(0);
	}
}

void splash_screen_render(void) {
	SDL_BlitSurface(splash_screen, NULL, screen, NULL);
}
