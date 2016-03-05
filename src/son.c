#include <assert.h>
#include "son.h"
#include "game_assets.h"

int init_son_t(son_t* s, float x, float y) {
	assert(s);
	if(son_down[0] == NULL) return -1;
	if(son_shadow == NULL) return -1;
	s->surf = son_down[0];
	s->shadow = son_shadow;
	s->x = x;
	s->y = y;
	s->xv = 0;
	s->yv = 0;
	s->base_speed = SON_BASE_SPEED;
	s->rect.w = s->surf->w;
	s->rect.h = s->surf->h;
	s->rect.x = (int)x;
	s->rect.y = (int)y;
	s->shadow_rect.w = s->shadow->w;
	s->shadow_rect.h = s->shadow->h;
	s->shadow_rect.x = (int)x - 9;
	s->shadow_rect.y = (int)(y + s->surf->h - 25);
	return 0;
}

void blit_son_t(son_t* s, SDL_Surface* dest) {
	assert(s);
	SDL_BlitSurface(s->shadow, NULL, dest, &s->shadow_rect);
	SDL_BlitSurface(s->surf, NULL, dest, &s->rect);
}

void update_son_t(son_t* s, const Uint8* keys) {
	s->xv = 0;
	s->yv = 0;
	
	if (keys[SDL_SCANCODE_W]) {
		s->yv = -s->base_speed;
	}
	if (keys[SDL_SCANCODE_S]) {
		s->yv = s->base_speed;
	}
	if (keys[SDL_SCANCODE_D]) {
		s->xv = s->base_speed;
	}
	if (keys[SDL_SCANCODE_A]) {
		s->xv = -s->base_speed;
	}

	s->x += s->xv;
	s->y += s->yv;
	s->rect.x = (int)s->x;
	s->rect.y = (int)s->y;
	s->shadow_rect.x = (int)s->x - 9;
	s->shadow_rect.y = (int)(s->y + s->surf->h - 30);
}

void destroy_son_t(son_t** s) {
	assert(s);
	assert(*s);
	free(*s);
	*s = NULL;
}
