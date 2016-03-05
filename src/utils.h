#ifndef _UTILS_H
#define _UTILS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

SDL_Surface* load_image(const char* path);

#ifdef DEBUG
    #if (DEBUG == 0)
        #define ASSETS_PATH "assets"
        #define CONFIG_PATH "config"
    #else
        #define ASSETS_PATH "../assets"
        #define CONFIG_PATH "../config"
    #endif
#else
    #define ASSETS_PATH "assets"
    #define CONFIG_PATH "config"
#endif

#endif
