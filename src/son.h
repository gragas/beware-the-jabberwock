#ifndef _SON_H
#define _SON_H

#include <SDL2/SDL.h>

#define SON_BASE_SPEED 0.125
#define SON_RUN_MULTIPLIER 2.0
#define SON_BASE_MAX_HEALTH 15
#define SON_BASE_MAX_ENERGY 15
#define SON_BASE_MAX_SPIRIT 10

typedef struct Son {
	SDL_Surface *surf, *shadow;
	SDL_Rect rect, shadow_rect;
	float x, y, xv, yv;
	float base_speed;
	int running, dir;
	int ticks;
	float max_health, max_energy, max_spirit;
	float health, energy, spirit;
} son_t;

int init_son_t(son_t* s, float x, float y);
void blit_son_t(son_t* s, SDL_Surface* dest);
int update_son_t(son_t* s, const Uint8* keys);
void destroy_son_t(son_t** s);

#endif
