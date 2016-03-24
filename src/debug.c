#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "main_menu.h"
#include "channel.h"
#include "debug.h"
#include "game_assets.h"
#include "son.h"

void init_debug() {
	/* main loop functions */
	poll_events = debug_poll_events;
	update = debug_update;
	render = debug_render;
	/* end main loop functions */

	destroy_main_menu();

	if(load_game_assets() == -1) {
		fprintf(stderr, "Failed to load game assets.\n");
		exit(-1);
	}

	son = malloc(sizeof(son_t));
	if (init_son_t(son, w_width / 2, w_height / 2) == -1) {
		fprintf(stderr, "Failed to initialize son.\n");
		exit(-1);
	}

#define TEMPERATURE_HGRID 100
#define HUMIDITY_HGRID 100
#define SPIRIT_HGRID 100

	/* initialize channels */
	init_channel_t(&temperature, TEMPERATURE_HGRID, 70.0f);
	init_channel_t(&humidity, HUMIDITY_HGRID, 100.0f);
	init_channel_t(&spirit, SPIRIT_HGRID, 1.0f);
	/* end initialize channels */
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
	const Uint8* keys = SDL_GetKeyboardState(NULL);
	update_son_t(son, keys);
}

void debug_render(void)
{
	SDL_FillRect(screen, NULL,
				 SDL_MapRGBA(screen->format,
							 0xFF, 0xEE, 0xCC, 0xFF));
	blit_son_t(son, screen);
}

void destroy_debug() {
	destroy_game_assets();
	destroy_son_t(&son);
}
