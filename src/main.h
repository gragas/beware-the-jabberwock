#ifndef _MAIN_H
#define _MAIN_H
#endif

#include <SDL2/SDL.h>

int init();
int load_assets();
void quit();

SDL_Window* window;
SDL_Surface* screen;
int w_width, w_height;
int fps, ticks_per_frame;
int exit_SDL;

void (*poll_events)(SDL_Event* event);
void (*update)(void);
void (*render)(void);
