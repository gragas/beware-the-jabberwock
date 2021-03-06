#ifndef _SPLASH_SCREEN_H
#define _SPLASH_SCREEN_H

void init_splash_screen();
void splash_screen_poll_events(SDL_Event* event);
void splash_screen_update(void);
void splash_screen_render(void);
void destroy_splash_screen(void);

SDL_Surface* splash_screen;
SDL_Rect splash_screen_rect;

int total_ticks;

#endif
