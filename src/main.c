#include <assert.h>
#include <stdio.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "main.h"
#include "utils.h"
#include "splash_screen.h"

#ifdef DEBUG
    #if (DEBUG == 0)
        #define ASSETS_PATH "assets"
        #define CONFIG_PATH "config"
    #else
        #define ASSETS_PATH "../assets"
        #define CONFIG_PATH "../config"
    #endif
#else
    #define ASSETS_PATH "assets"
    #define CONFIG_PATH "config"
#endif

int main() {
	if (init() != 0) {
		fprintf(stderr, "Failed to initialize game.\n");
		return EXIT_FAILURE;
	}

	if (load_assets() != 0) {
		fprintf(stderr, "Failed to load assets.\n");
		return EXIT_FAILURE;
	}
	
	SDL_Event event;

	ticks = 0;
	
	while (exit_SDL == 0) {
		
		poll_events(&event);
		update();
		render();
		
		SDL_UpdateWindowSurface(window);
		
		delta = SDL_GetTicks() - ticks;
		if (delta < ticks_per_frame) {
			SDL_Delay(ticks_per_frame - delta);
			ticks = SDL_GetTicks();
		}
	}
	
    quit();
	return EXIT_SUCCESS;
}

int init() {
	exit_SDL = 0;
	window = NULL;
	screen = NULL;

	FILE* file = fopen(CONFIG_PATH".txt", "r");
	if (file == NULL)
	{
		w_width = 1024;
		w_height = 768;
	}
	else
	{
		char* line_buffer = NULL;
		size_t nbytes = 0;
		while(getline(&line_buffer, &nbytes, file) != -1) {
			char* token = strtok(line_buffer, ":");
			if (token == NULL) continue;
			if (strcmp(token, "width") == 0) {
				token = strtok(NULL, ":");
				char* endptr = token+strlen(token)-1;
				long value = strtol(token, &endptr, 10);
				if (value > 0 && value <= 3840) {
					w_width = value;
				}
			} else if (strcmp(token, "height") == 0) {
				token = strtok(NULL, ":");
				char* endptr = token+strlen(token)-1;
				long value = strtol(token, &endptr, 10);
				if (value > 0 && value <= 3840) {
					w_height = value;
				}
			}
		}
	}

	fps = 60;
	ticks_per_frame = 1000 / fps;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		fprintf(stderr, "SDL failed to initialize.\n");
		return -1;
	}

	window = SDL_CreateWindow("Beware The Jabberwock",
							  SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
							  w_width, w_height, SDL_WINDOW_SHOWN);
	if (window == NULL) {
		fprintf(stderr, "SDL failed to create window.\n");
		return -1;		
	}

	screen = SDL_GetWindowSurface(window);
	screen->format->format = SDL_PIXELFORMAT_RGBA8888;
	if (SDL_BYTEORDER == SDL_BIG_ENDIAN) {
		screen->format->Amask = 0x000000FF;
	} else {
		screen->format->Amask = 0xFF000000;
	}
	SDL_FillRect(screen, NULL, SDL_MapRGBA(screen->format, 0x00, 0x00, 0xFF, 0xFF));

	poll_events = splash_screen_poll_events;
	update = splash_screen_update;
	render = splash_screen_render;

	return 0;
}

int load_assets() {
	int img_flags = IMG_INIT_PNG;
	if (!(IMG_Init(img_flags) & img_flags)) {
		fprintf(stderr, "Could not initialize SDL_image.\n");
		return -1;
	}

	splash_screen = load_image(ASSETS_PATH"/splash_screen/splash_screen.png");
	if (splash_screen == NULL) return -1;
	return 0;
}

void quit() {
	assert(window);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
