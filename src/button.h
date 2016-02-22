#include <SDL2/SDL.h>

#ifndef _BUTTON_H
#define _BUTTON_H

typedef struct button {
	size_t x, y, w, h;
	void (*func)(void);
	SDL_Rect rect;
	SDL_Surface* up_surface;
	SDL_Surface* down_surface;
	SDL_Surface* surface;
} button_t;

button_t* Button(
	size_t x, size_t y,
	SDL_Surface* up_surface, SDL_Surface* down_surface,
	void (*func)(void)
	);

void Button_set_pos(button_t* b, int x, int y);

int Button_within(button_t* b, int x, int y);

void Button_destroy(button_t* b);

void Button_blit(button_t* b, SDL_Surface* dest);

void Button_press(button_t* b);

void Button_release(button_t* b, int call_func);

#endif
