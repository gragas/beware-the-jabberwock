#include <SDL2/SDL.h>
#include "utils.h"
#include "son_hud.h"
#include "main.h"

void init_son_hud_t(son_hud_t* son_hud, son_t* son, int x, int y) {
	son_hud->son = son;
	#define DEFAULT_TTF_FONT_NAME FONT_PATH"/LiberationMono-Regular.ttf"
    #define DEFAULT_TTF_FONT_SIZE 18
	init_label_t(&son_hud->name_label, son_hud->son->name,
				 x, y,
				 DEFAULT_TTF_FONT_NAME, DEFAULT_TTF_FONT_SIZE,
				 0x00, 0x00, 0x00,
				 0xFF);
	son_hud->name_label.rect.y -= son_hud->name_label.rect.h + SON_HUD_PADDING;
	son_hud->health_rect.x = x;
	son_hud->health_rect.y = y;
	son_hud->health_rect.w = SON_HUD_WIDTH;
	son_hud->health_rect.h = SON_HUD_HEIGHT;
	son_hud->health_surf = SDL_CreateRGBSurface(0,
												son_hud->health_rect.w,
												son_hud->health_rect.h,
												32, 0, 0, 0, 0);
	son_hud->energy_rect.x = x;
	son_hud->energy_rect.y = y + SON_HUD_HEIGHT + SON_HUD_PADDING;
	son_hud->energy_rect.w = SON_HUD_WIDTH;
	son_hud->energy_rect.h = SON_HUD_HEIGHT;
	son_hud->energy_surf = SDL_CreateRGBSurface(0,
												son_hud->energy_rect.w,
												son_hud->energy_rect.h,
												32, 0, 0, 0, 0);
	son_hud->spirit_rect.x = x;
	son_hud->spirit_rect.y = y + (SON_HUD_HEIGHT + SON_HUD_PADDING) * 2;
	son_hud->spirit_rect.w = SON_HUD_WIDTH;
	son_hud->spirit_rect.h = SON_HUD_HEIGHT;
	son_hud->spirit_surf = SDL_CreateRGBSurface(0,
												son_hud->spirit_rect.w,
												son_hud->spirit_rect.h,
												32, 0, 0, 0, 0);
	render_son_hud_t(son_hud);
}

void blit_son_hud_t(son_hud_t* son_hud, SDL_Surface* dest) {
	blit_label_t(&son_hud->name_label, dest);
	SDL_BlitSurface(son_hud->health_surf, NULL, dest, &son_hud->health_rect);
	SDL_BlitSurface(son_hud->energy_surf, NULL, dest, &son_hud->energy_rect);
	SDL_BlitSurface(son_hud->spirit_surf, NULL, dest, &son_hud->spirit_rect);
}

void render_son_hud_t(son_hud_t* son_hud) {
	SDL_FillRect(son_hud->health_surf, NULL,
				 SDL_MapRGBA(screen->format,
							 SON_HUD_HEALTH_R, SON_HUD_HEALTH_G, SON_HUD_HEALTH_B,
							 SON_HUD_A));
	SDL_FillRect(son_hud->energy_surf, NULL,
				 SDL_MapRGBA(screen->format,
							 SON_HUD_ENERGY_R, SON_HUD_ENERGY_G, SON_HUD_ENERGY_B,
							 SON_HUD_A));
	SDL_FillRect(son_hud->spirit_surf, NULL,
				 SDL_MapRGBA(screen->format,
							 SON_HUD_SPIRIT_R, SON_HUD_SPIRIT_G, SON_HUD_SPIRIT_B,
							 SON_HUD_A));
}
