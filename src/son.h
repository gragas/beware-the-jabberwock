#ifndef _SON_H
#define _SON_H

#include <SDL2/SDL.h>

#define SON_BASE_SPEED 0.125
#define SON_RUN_MULTIPLIER 2.0

typedef struct Son {
	SDL_Surface *surf, *shadow;
	SDL_Rect rect, shadow_rect;
	float x, y, xv, yv;
	float base_speed;
	int running;
	int ticks;
} son_t;

int init_son_t(son_t* s, float x, float y);
void blit_son_t(son_t* s, SDL_Surface* dest);
void update_son_t(son_t* s, const Uint8* keys);
void destroy_son_t(son_t** s);

#endif
