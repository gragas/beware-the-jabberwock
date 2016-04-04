#ifndef _SON_HUD_H
#define _SON_HUD_H

#include <SDL2/SDL.h>
#include "son.h"
#include "label.h"

#define SON_HUD_WIDTH 150
#define SON_HUD_HEIGHT 20
#define SON_HUD_PADDING 7
#define SON_HUD_HEALTH_R 0xFF
#define SON_HUD_HEALTH_G 0x00
#define SON_HUD_HEALTH_B 0x00
#define SON_HUD_ENERGY_R 0xFF
#define SON_HUD_ENERGY_G 0xFF
#define SON_HUD_ENERGY_B 0x00
#define SON_HUD_SPIRIT_R 0x00
#define SON_HUD_SPIRIT_G 0x00
#define SON_HUD_SPIRIT_B 0xFF
#define SON_HUD_A 0xFF

typedef struct son_hud {
	label_t name_label;
	SDL_Surface *health_surf, *energy_surf, *spirit_surf;
	SDL_Rect health_rect, energy_rect, spirit_rect;
	son_t* son;
} son_hud_t;

void init_son_hud_t(son_hud_t* son_hud, son_t* son, int x, int y);
void blit_son_hud_t(son_hud_t* son_hud, SDL_Surface* dest);
void render_son_hud_t(son_hud_t* son_hud);

#endif
