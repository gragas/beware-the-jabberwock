#ifndef _GAME_ASSETS_H
#define _GAME_ASSETS_H

#include <SDL2/SDL.h>

int load_game_assets(void);
void destroy_game_assets(void);

#define NUM_SON_STATIONARY 1
SDL_Surface** son_stationary;
#define NUM_SON_DOWN 4
SDL_Surface** son_down;
#define NUM_SON_UP 4
SDL_Surface** son_up;
SDL_Surface* son_shadow;

SDL_Surface* bedrock_sand_0;
SDL_Surface* bedrock_sand_1;
SDL_Surface* bedrock_sand_2;
SDL_Surface* bedrock_sand_3;
SDL_Surface* bedrock_sand_4;

#endif
