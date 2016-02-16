#ifndef _SPLASH_SCREEN_H
#define _SPLASH_SCREEN_H
#endif

void splash_screen_poll_events(SDL_Event* event);
void splash_screen_update(void);
void splash_screen_render(void);

SDL_Surface* splash_screen;
