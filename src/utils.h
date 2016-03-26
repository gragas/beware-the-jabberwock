#ifndef _UTILS_H
#define _UTILS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

SDL_Surface* load_image(const char* path);

#define TILE_SIZE 32

#ifdef DEBUG
    #if (DEBUG == 0)
        #define ASSETS_PATH "assets"
        #define CONFIG_PATH "config"
        #define FONT_PATH "fonts"
    #else
        #define ASSETS_PATH "../assets"
        #define CONFIG_PATH "../config"
        #define FONT_PATH "../fonts"
    #endif
#else
    #define ASSETS_PATH "assets"
    #define CONFIG_PATH "config"
    #define FONT_PATH "fonts"
#endif

#endif
