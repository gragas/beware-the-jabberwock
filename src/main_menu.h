#ifndef _MAIN_MENU_H
#define _MAIN_MENU_H

#include "button.h"

void init_main_menu(void);
void main_menu_poll_events(SDL_Event* event);
void main_menu_update(void);
void main_menu_render(void);
void destroy_main_menu(void);

#define NUM_MAIN_MENU_BUTTONS 3
button_t* main_menu_buttons[NUM_MAIN_MENU_BUTTONS];
button_t* main_menu_debug_button;
button_t* main_menu_exit_button;
button_t* main_menu_create_character_button;

#endif
