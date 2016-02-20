#ifndef _MAIN_H
#define _MAIN_H
#endif

#include <SDL2/SDL.h>

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

int init();
int load_assets();
void quit();

SDL_Window* window;
SDL_Surface* screen;
int fullscreen;
int w_width, w_height;
int delta, ticks;
int fps, ticks_per_frame;
int exit_SDL;

void (*poll_events)(SDL_Event* event);
void (*update)(void);
void (*render)(void);
