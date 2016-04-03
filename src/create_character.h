#ifndef _CREATE_CHARACTER_H
#define _CREATE_CHARACTER_H

#include "button.h"

void init_create_character(void);
void create_character_poll_events(SDL_Event* event);
void create_character_update(void);
void create_character_render(void);
void destroy_create_character(void);

#define NUM_CREATE_CHARACTER_BUTTONS 1
button_t* create_character_buttons[NUM_CREATE_CHARACTER_BUTTONS];
button_t* create_character_back_button;

#endif
