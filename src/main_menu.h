#ifndef _MAIN_MENU_H
#define _MAIN_MENU_H
#endif

void init_main_menu();
void main_menu_poll_events(SDL_Event* event);
void main_menu_update(void);
void main_menu_render(void);

SDL_Surface* main_menu_debug_button;
SDL_Rect main_menu_debug_button_rect;
