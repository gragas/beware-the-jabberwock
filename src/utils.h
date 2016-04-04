#ifndef _UTILS_H
#define _UTILS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

SDL_Surface* load_image(const char* path);

#define TILE_SIZE 16

#ifdef DEBUG
    #if (DEBUG == 0)
        #define ASSETS_PATH "assets"
        #define CONFIG_PATH "config"
        #define FONT_PATH "fonts"
        #define SAVE_PATH "saves"
        #define CHARACTER_SAVE_PATH SAVE_PATH"/characters"
        #define MAP_SAVE_PATH SAVE_PATH"/maps"
    #else
        #define ASSETS_PATH "../assets"
        #define CONFIG_PATH "../config"
        #define FONT_PATH "../fonts"
        #define SAVE_PATH "../saves"
        #define CHARACTER_SAVE_PATH SAVE_PATH"/characters"
        #define MAP_SAVE_PATH SAVE_PATH"/maps"
    #endif
#else
    #define ASSETS_PATH "assets"
    #define CONFIG_PATH "config"
    #define FONT_PATH "fonts"
    #define SAVE_PATH "saves"
    #define CHARACTER_SAVE_PATH SAVE_PATH"/characters"
    #define MAP_SAVE_PATH SAVE_PATH"/maps"
#endif



#endif
