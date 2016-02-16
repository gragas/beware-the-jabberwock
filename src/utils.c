#include <assert.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "main.h"
#include "utils.h"

SDL_Surface* load_image(const char* path) {
	assert(path);
	SDL_Surface* result = NULL;
	SDL_Surface* loaded = IMG_Load(path);
	if (loaded == NULL) {
		fprintf(stderr, "Unable to load \"%s\".\n", path);
		return NULL;
	}
	result = SDL_ConvertSurface(loaded, screen->format, 0);
	SDL_FreeSurface(loaded);
	if (result == NULL) {
		fprintf(stderr, "Unable to optimize \"%s\".\n", path);
		return NULL;
	}
	return result;
}
