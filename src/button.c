#include <assert.h>
#include "button.h"

button_t* Button(
	size_t x, size_t y,
	SDL_Surface* up_surface, SDL_Surface* down_surface,
	void (*func)(void)
	)
{
	// asserts
	assert(up_surface);
	assert(down_surface);
	assert(up_surface->w == down_surface->w);
	assert(up_surface->h == down_surface->h);
	// the actual struct
	button_t* b = malloc(sizeof(button_t));
	// trivial instance variables
	b->x = x;
	b->y = y;
	b->func = func;
	b->up_surface = up_surface;
	b->down_surface = down_surface;
	b->surface = up_surface;
	// b->rect
	b->rect.x = b->x;
	b->rect.y = b->y;
	b->rect.w = b->surface->w;
	b->rect.h = b->surface->h;
	b->w = b->rect.w;
	b->h = b->rect.h;
	return b;
}

void Button_set_pos(button_t* b, int x, int y)
{
	assert(b);
	b->x = x;
	b->y = y;
	b->rect.x = b->x;
	b->rect.y = b->y;
}

int Button_within(button_t* b, int x, int y)
{
	assert(b);
	return x >= b->x && x <= b->x + b->w && y >= b->y && y <= b->y + b->h;
}

void Button_destroy(button_t* b)
{
	assert(b);
	free(b);
}

void Button_blit(button_t* b, SDL_Surface* dest)
{
	assert(b);
	SDL_BlitSurface(b->surface, NULL, dest, &b->rect);
}

void Button_press(button_t* b)
{
	assert(b);
	b->surface = b->down_surface;
}

void Button_release(button_t* b, int call_func)
{
	assert(b);
	b->surface = b->up_surface;
	if(call_func && b->func != NULL) {
		b->func();
	}
}
