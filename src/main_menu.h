#ifndef _MAIN_MENU_H
#define _MAIN_MENU_H

#include "button.h"

void init_main_menu();
void main_menu_poll_events(SDL_Event* event);
void main_menu_update(void);
void main_menu_render(void);
void destroy_main_menu();

#define NUM_MAIN_MENU_BUTTONS 2
static button_t* buttons[NUM_MAIN_MENU_BUTTONS];
static button_t* debug_button;
static button_t* exit_button;

#endif
