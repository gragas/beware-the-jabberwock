#ifndef _MAIN_H
#define _MAIN_H

#include <SDL2/SDL.h>

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

// Assets
SDL_Surface* main_menu_debug_button_up;
SDL_Surface* main_menu_debug_button_down;
SDL_Surface* main_menu_exit_button_up;
SDL_Surface* main_menu_exit_button_down;
SDL_Surface* main_menu_create_character_button_up;
SDL_Surface* main_menu_create_character_button_down;
SDL_Surface* create_character_back_button_up;
SDL_Surface* create_character_back_button_down;
SDL_Surface* create_character_create_button_up;
SDL_Surface* create_character_create_button_down;

#endif
