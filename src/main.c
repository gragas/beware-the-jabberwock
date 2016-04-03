#include <assert.h>
#include <stdio.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "main.h"
#include "utils.h"
#include "splash_screen.h"
#include "main_menu.h"

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
		ticks = SDL_GetTicks();
		if (delta < ticks_per_frame) {
			SDL_Delay(ticks_per_frame - delta);
		}
	}
	
    quit();
	return EXIT_SUCCESS;
}

int init() {
	/* Initialize */
	exit_SDL = 0;
	window = NULL;
	screen = NULL;

	w_width = 1024;
	w_height = 768;
	fullscreen = 0;
	/* End initialize */

	/* Load options from config file */
	FILE* file = fopen(CONFIG_PATH".txt", "r");
	if (file != NULL)
	{
		char* line_buffer = NULL;
		size_t nbytes = 0;
		while(getline(&line_buffer, &nbytes, file) != -1) {
			char* token = strtok(line_buffer, ":");
			if (token == NULL) continue;
			if (strcmp(token, "width") == 0) {
				token = strtok(NULL, ":");
				if (token == NULL) continue;
				char* endptr = token+strlen(token)-1;
				long value = strtol(token, &endptr, 10);
				if (value > 0 && value <= 3840) {
					w_width = value;
				}
			} else if (strcmp(token, "height") == 0) {
				token = strtok(NULL, ":");
				if (token == NULL) continue;
				char* endptr = token+strlen(token)-1;
				long value = strtol(token, &endptr, 10);
				if (value > 0 && value <= 3840) {
					w_height = value;
				}
			} else if (strcmp(token, "fullscreen") == 0) {
				token = strtok(NULL, ":");
				if (token == NULL) continue;
				char* endptr = token+strlen(token)-1;
				long value = strtol(token, &endptr, 10);
				if (value != 0) {
					fullscreen = SDL_WINDOW_FULLSCREEN_DESKTOP;
				}
			}
		}
	}
	/* End load options from config file */

	fps = 60;
	ticks_per_frame = 1000 / fps;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		fprintf(stderr, "SDL failed to initialize.\n");
		return -1;
	}

	window = SDL_CreateWindow("Beware The Jabberwock",
							  SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
							  w_width, w_height, SDL_WINDOW_SHOWN | fullscreen);

	if (fullscreen) {
		SDL_DisplayMode mode = { SDL_PIXELFORMAT_UNKNOWN, 0, 0, 0, 0 };
		if (SDL_GetDisplayMode(0, 0, &mode) != 0) {
			fprintf(stderr, "Could not get display mode.\n");
			return -1;
		}
		w_width = mode.w;
		w_height = mode.h;
	}
	
	if (window == NULL) {
		fprintf(stderr, "SDL failed to create window.\n");
		return -1;		
	}

	/* Change the screen format from RGB -> RGBA */
	screen = SDL_GetWindowSurface(window);
	screen->format->format = SDL_PIXELFORMAT_RGBA8888;
	if (SDL_BYTEORDER == SDL_BIG_ENDIAN) {
		screen->format->Amask = 0x000000FF;
	} else {
		screen->format->Amask = 0xFF000000;
	}
	/* End change the screen format from RGB -> RGBA */
	
	/* Initialize the truetype font API */
	if (TTF_Init() == -1) {
		fprintf(stderr, "TTF_Init: %s\n", TTF_GetError());
		return -1;
	}
	/* End initialize the truetype font API */

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

	init_splash_screen();

	main_menu_debug_button_up = load_image(
		ASSETS_PATH"/main_menu/debug_button.png");
	if (main_menu_debug_button_up == NULL) return -1;

	main_menu_debug_button_down = load_image(
		ASSETS_PATH"/main_menu/debug_button_clicked.png");
	if (main_menu_debug_button_down == NULL) return -1;

	main_menu_exit_button_up = load_image(
		ASSETS_PATH"/main_menu/exit_button.png");
	if (main_menu_exit_button_up == NULL) return -1;

	main_menu_exit_button_down = load_image(
		ASSETS_PATH"/main_menu/exit_button_clicked.png");
	if (main_menu_exit_button_down == NULL) return -1;

	main_menu_create_character_button_up = load_image(
		ASSETS_PATH"/main_menu/create_character_button.png");
	if (main_menu_create_character_button_up == NULL) return -1;

	main_menu_create_character_button_down = load_image(
		ASSETS_PATH"/main_menu/create_character_button_clicked.png");
	if (main_menu_create_character_button_down == NULL) return -1;

	create_character_back_button_up = load_image(
		ASSETS_PATH"/create_character/create_character_back_button.png");
	if (create_character_back_button_up == NULL) return -1;

	create_character_back_button_down = load_image(
		ASSETS_PATH"/create_character/create_character_back_button_clicked.png");
	if (create_character_back_button_down == NULL) return -1;

	return 0;
}

void quit() {
	assert(window);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
