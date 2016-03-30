#include <assert.h>
#include <stdio.h>
#include "son.h"
#include "game_assets.h"
#include "main.h"

int init_son_t(son_t* s, float x, float y) {
	assert(s);
	if(son_down[0] == NULL) return -1;
	if(son_shadow == NULL) return -1;
	s->surf = son_stationary[0];
	s->shadow = son_shadow;
	s->x = x;
	s->y = y;
	s->xv = 0;
	s->yv = 0;
	s->base_speed = SON_BASE_SPEED;
	s->running = 0;
	s->dir = 0x00; /* stationary = 0x_0; moving = 0x_1;
					* down = 0x0_; up = 0x1_;
					* left = 0x2_; right = 0x3_; */
	s->rect.w = s->surf->w;
	s->rect.h = s->surf->h;
	s->rect.x = (int)x;
	s->rect.y = (int)y;
	s->shadow_rect.w = s->shadow->w;
	s->shadow_rect.h = s->shadow->h;
	s->shadow_rect.x = (int)x - 5;
	s->shadow_rect.y = (int)(y + s->surf->h - 12);
	s->max_health = SON_BASE_MAX_HEALTH;
	s->max_energy = SON_BASE_MAX_ENERGY;
	s->max_spirit = SON_BASE_MAX_SPIRIT;
	s->health = s->max_health;
	s->energy = s->max_energy;
	s->spirit = s->max_spirit;
	return 0;
}

void blit_son_t(son_t* s, SDL_Surface* dest) {
	SDL_BlitSurface(s->shadow, NULL, dest, &s->shadow_rect);
	SDL_BlitSurface(s->surf, NULL, dest, &s->rect);
}

/* returns a non-zero number if health, energy, or spirit have changed */
int update_son_t(son_t* s, const Uint8* keys) {
	int return_value = 0;
	s->xv = 0.0f;
	s->yv = 0.0f;
	
	s->dir = 0x00;
	
	if (keys[SDL_SCANCODE_W]) { s->yv = -s->base_speed; s->dir = 0x11; }
	if (keys[SDL_SCANCODE_S]) { s->yv =  s->base_speed; s->dir = 0x01; }
	if (keys[SDL_SCANCODE_D]) { s->xv =  s->base_speed; s->dir = 0x31; }
	if (keys[SDL_SCANCODE_A]) { s->xv = -s->base_speed; s->dir = 0x21; }
	if (keys[SDL_SCANCODE_LSHIFT]) s->running = 1; else s->running = 0;
	
	if (s->dir & 0x01) { // if moving
		switch(s->dir) {
		case 0x01: // down
			s->surf = son_down[(s->ticks / 300) % NUM_SON_DOWN];
			break;
		case 0x11: // up
			s->surf = son_up[(s->ticks / 300) % NUM_SON_UP];
			break;
		default:
			break;
		}
	} else if (s->dir == 0x00) { // if stationary
		s->surf = son_stationary[(s->ticks / 300) % NUM_SON_STATIONARY];
	} else {
		fprintf(stderr, "Something unintended happened around line %d\n", __LINE__);
		exit(1);
	}

	float mult = (float)delta;
	if (s->running) mult *= SON_RUN_MULTIPLIER;

	s->x += s->xv * mult;
	s->y += s->yv * mult;
	// s->rect.x = (int)s->x;
	// s->rect.y = (int)s->y;
	// s->shadow_rect.x = (int)s->x - 5;
	// s->shadow_rect.y = (int)(s->y + s->surf->h - 12);
	s->ticks += delta;
	return return_value;
}

void destroy_son_t(son_t** s) {
	assert(s);
	assert(*s);
	free(*s);
	*s = NULL;
}
